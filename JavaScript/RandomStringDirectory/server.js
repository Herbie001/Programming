const express = require('express');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');
const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./BackEnd/generated_strings.db');
const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname)));

db.run(`
    CREATE TABLE IF NOT EXISTS strings (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        type TEXT,
        value TEXT,
        timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    `);

function saveString(type, value) {
    db.run(`INSERT INTO strings (type, value) VALUES (?,?)`, [type,value], (err) => {
        if(err) {
            console.log('Database insert error:' , err);
        }
    });
}

app.get(`/api/stored-strings`, (req, res) => {
    db.all(`SELECT * FROM strings ORDER by timestamp DESC`, [], (err, rows) => {
        if(err) {
            res.status(500).send('Error fetching stored strings.');
            return;
        }
        res.json(rows);
    });
});
app.get(`/api/saved-strings`, (req, res) => {
    db.all("SELECT type, value FROM strings", [], (err, rows) => {
        if (err) {
            res.status(500).json({ success: false, error: err.message });
            return;
        }
        const data = rows.map(entry => `${entry.type}: ${entry.value}`).join('\n');
        const filePath = path.join(__dirname, 'stored_strings.txt');

        fs.writeFile(filePath, data, 'utf8', (writeErr) => {
            if (writeErr) {
                res.status(500).json({ success: false, error: writeErr.message });
                return;
            }
            res.download(filePath, 'stored_strings.txt', (downloadErr) => {
                if (downloadErr) {
                    res.status(500).json({ success: false, error: downloadErr.message });
                }
            });
        });
    });
});
app.get(`/api/random-string`, (req, res) => {
    const length = parseInt(req.query.length, 10);
    const stringType = req.query.stringType;
    if(isNaN(length) || length <= 0) {
        res.status(400).send('Invalid input length');
        return;
    }
    const command = `./BackEnd/randomStringGenerator.sh ${stringType} ${length}`;
    console.log(`Executing command: ${command}`);
    exec(command, (error, stdout, stderr) => {
        if(error) {
            console.error(`Execution error: ${error.message}`);
            res.status(500).send('Error executing C++ Program');
            return;
        }
        if(stderr) {
            console.error(`stderr: ${stderr}`);
        }
        console.log(`stdout from bash script: ${stdout}`);
        const filePath = path.join(__dirname, 'BackEnd', 'randomizedString.txt');
        
        fs.readFile(filePath, 'utf8', (err, data) => {
            if(err) {
                console.error(`Error reading file: ${err.message}`);
                res.status(500).send('Error reading random string');
                return
            }
            saveString(stringType, data.trim());
            console.log(`Random string read from file: $(data.trim()}`);
            res.send(data.trim());
        });
    });
});
app.delete('/api/clear-history', (req, res) => {
    db.get('SELECT COUNT(*) AS count FROM strings', [], (err, row) => {
        if (err) {
            res.status(500).json({ success: false, error: err.message });
            return;
        }
        if (row.count === 0) {
            res.json({ success: false, message: 'The database is empty and there are no strings to remove.' });
        } else {
            db.run('DELETE FROM strings', [], (deleteErr) => {
                if (deleteErr) {
                    res.status(500).json({ success: false, error: deleteErr.message });
                } else {
                    res.json({ success: true, message: 'History cleared successfully!' });
                }
            });
        }
    });
});
app.get(`/api/save-strings`, (req, res) => {
    db.all("SELECT type, value FROM strings", [], (err, rows) => {
        if (err) {
            res.status(500).json({ success: false, message: 'Database error: ' + err.message });
            return;
        }
        if (rows.length === 0) {
            res.status(400).json({ success: false, message: 'The database is empty. No strings to save.' });
            return;
        }
        const data = rows.map(entry => `${entry.type}: ${entry.value}`).join('\n');
        const filePath = path.join(__dirname, 'stored_strings.txt');

        fs.writeFile(filePath, data, 'utf8', (writeErr) => {
            if (writeErr) {
                res.status(500).json({ success: false, message: 'File writing error: ' + writeErr.message });
                return;
            }
            res.download(filePath, 'stored_strings.txt', (downloadErr) => {
                if (downloadErr) {
                    res.status(500).json({ success: false, message: 'File download error: ' + downloadErr.message });
                }
            });
        });
    });
});
app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});