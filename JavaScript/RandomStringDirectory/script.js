document.addEventListener('DOMContentLoaded', () => {
    const stringContainer = document.getElementById('string-container');
    const lengthInput = document.getElementById('length-input');
    const generateButton = document.getElementById('generate-button');
    const tabs = document.querySelectorAll('.tab-button');
    const saveButton = document.getElementById('save-button');
    const clearHistoryButton = document.getElementById('clear-history-button');
    let selectedType = 'randomAlphaString';

    tabs.forEach(tab => {
        tab.addEventListener('click', () => {
            selectedType = tab.getAttribute('data-type');
            console.log(`Selected stringType: ${selectedType}`);
            tabs.forEach(t => t.classList.remove('active'));
            tab.classList.add('active');
        });
    });
    generateButton.addEventListener('click', () => {
        const length = parseInt(lengthInput.value, 10);
        if (isNaN(length) || length <= 0) {
            alert('Please enter a valid positive integer for length');
            return;
        }
        console.log(`Sending request with type: ${selectedType}, length: ${length}`);

        fetch(`/api/random-string?stringType=${encodeURIComponent(selectedType)}&length=${length}`)
            .then(response => response.text())
            .then(randomString => {
                console.log(`Received random string: ${randomString}`);
                stringContainer.innerHTML = '';
                randomString.split('').forEach((char, index) => {
                    const span = document.createElement('span');
                    span.textContent = char;
                    span.style.animationDelay = `${index * 0.1}s`;
                    stringContainer.appendChild(span);
                });
                fetchStoredStrings();
            })
            .catch(error => {
                console.error('Error fetching random string:', error);
                stringContainer.textContent = 'Error loading random string';
            });
    });
    saveButton.addEventListener('click', () => {
        fetch(`/api/save-strings`)
            .then(response => {
                if (!response.ok) throw new Error('Failed to save file.');
                return response.blob(); // Expecting a file (not JSON)
            })
            .then(blob => {
                const url = window.URL.createObjectURL(blob);
                const a = document.createElement('a');
                a.href = url;
                a.download = 'stored_strings.txt';
                document.body.appendChild(a);
                a.click();
                document.body.removeChild(a);
            })
            .catch(error => alert('Error saving string: ' + error.message));
    });
    clearHistoryButton.addEventListener('click', () => {
        if (confirm("Are you sure you want to clear the history? This action cannot be undone.")) {
            fetch('/api/clear-history', { method: 'DELETE' })
                .then(response => response.json())
                .then(data => {
                    alert(data.message);
                    fetchStoredStrings(); // Refresh the displayed history
                })
                .catch(error => console.error('Error clearing history:', error));
        }
    });
    fetchStoredStrings();
});
/**
 * This functions purpose is to fetch all the strings in the database
 */
function fetchStoredStrings() {
    fetch(`/api/stored-strings`)
        .then(response => response.json())
        .then(strings => {
            const historyContainer = document.getElementById('history-container');
            historyContainer.innerHTML = '';
            strings.forEach(entry => {
                const div = document.createElement('div');
                div.classList.add('history-entry');
                div.textContent = `${entry.value}`;
                historyContainer.appendChild(div);
            });
        })
        .catch(error => console.error('Error fetching stored strings:', error));
}