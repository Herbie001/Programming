## Hello! This is the Graph Properties markdown file!

# Program Objective 

The objective of this program is to answer essential questions about a graph. How many edges? How many nodes? How many neighbors? Can we get from node u to node v and if so does there exist a shortest path? 

# How to compile and run the program

So far, there are the following tests: graph_properties, shortest_unweighted, shortest_weighted, connected_components, and smallest_threshold.

1. Adjust your directory, type 'make' in console to active Makefile.
2. Run the following './GraphTest ./Examples/small-graph.csv x' where x denotes one of the test specified above.

# Time complexity




# Examples

In this directory, you will notice a subdirectory called 'Examples'. There you will find a relatively small graph consisting of seven vertices.
Here is the are some example outputs.

First is the graph properties test:

Number of Nodes 7
Nodes   {"A","B","C","D","E","F","G"}
Number of Edges 6
Edge Weights    {"A":{"A":-1,"B":0.1,"C":0.5,"D":-1,"E":-1,"F":-1,"G":-1},"B":{"A":0.1,"B":-1,"C":0.1,"D":0.1,"E":-1,"F":-1,"G":-1},"C":{"A":0.5,"B":0.1,"C":-1,"D":-1,"E":-1,"F":-1,"G":-1},"D":{"A":-1,"B":0.1,"C":-1,"D":-1,"E":-1,"F":-1,"G":-1},"E":{"A":-1,"B":-1,"C":-1,"D":-1,"E":-1,"F":0.4,"G":-1},"F":{"A":-1,"B":-1,"C":-1,"D":-1,"E":0.4,"F":-1,"G":0.5},"G":{"A":-1,"B":-1,"C":-1,"D":-1,"E":-1,"F":0.5,"G":-1}}
Number of Neighbors     {"A":2,"B":3,"C":2,"D":1,"E":1,"F":2,"G":1}
Neighbors       {"A":{"C","B"},"B":{"D","C","A"},"C":{"B","A"},"D":{"B"},"E":{"F"},"F":{"G","E"},"G":{"F"}}


Next is the shortest unweighted path:

Shortest Path (Unweighted)      
{"A":{"A":["A"],"B":["A","B"],"C":["A","C"],"D":["A","B","D"],"E":[],"F":[],"G":[]},
"B":{"A":["B","A"],"B":["B"],"C":["B","C"],"D":["B","D"],"E":[],"F":[],"G":[]},
"C":{"A":["C","A"],"B":["C","B"],"C":["C"],"D":["C","B","D"],"E":[],"F":[],"G":[]},
"D":{"A":["D","B","A"],"B":["D","B"],"C":["D","B","C"],"D":["D"],"E":[],"F":[],"G":[]},
"E":{"A":[],"B":[],"C":[],"D":[],"E":["E"],"F":["E","F"],"G":["E","F","G"]},
"F":{"A":[],"B":[],"C":[],"D":[],"E":["F","E"],"F":["F"],"G":["F","G"]},
"G":{"A":[],"B":[],"C":[],"D":[],"E":["G","F","E"],"F":["G","F"],"G":["G"]}}


Next is the shortest weighted path:

Shortest Path (Weighted)        
{"A":{"A":[["A","A",-1]],"B":[["A","B",0.1]],"C":[["A","B",0.1],["B","C",0.1]],"D":[["A","B",0.1],["B","D",0.1]],"E":[],"F":[],"G":[]},
"B":{"A":[["B","A",0.1]],"B":[["B","B",-1]],"C":[["B","C",0.1]],"D":[["B","D",0.1]],"E":[],"F":[],"G":[]},
"C":{"A":[["C","B",0.1],["B","A",0.1]],"B":[["C","B",0.1]],"C":[["C","C",-1]],"D":[["C","B",0.1],["B","D",0.1]],"E":[],"F":[],"G":[]},
"D":{"A":[["D","B",0.1],["B","A",0.1]],"B":[["D","B",0.1]],"C":[["D","B",0.1],["B","C",0.1]],"D":[["D","D",-1]],"E":[],"F":[],"G":[]},
"E":{"A":[],"B":[],"C":[],"D":[],"E":[["E","E",-1]],"F":[["E","F",0.4]],"G":[["E","F",0.4],["F","G",0.5]]},
"F":{"A":[],"B":[],"C":[],"D":[],"E":[["F","E",0.4]],"F":[["F","F",-1]],"G":[["F","G",0.5]]},
"G":{"A":[],"B":[],"C":[],"D":[],"E":[["G","F",0.5],["F","E",0.4]],"F":[["G","F",0.5]],"G":[["G","G",-1]]}}


Next is the connected components:

onnected Components (threshold = 0.1)  [{"A","B","D","C"},{"E"},{"F"},{"G"}]


Finally, we have the smallest connecting threshold:

Smallest Connecting Threshold   
{"A":{"A":0,"B":0.1,"C":0.1,"D":0.1,"E":-1,"F":-1,"G":-1},
"B":{"A":0.1,"B":0,"C":0.1,"D":0.1,"E":-1,"F":-1,"G":-1},
"C":{"A":0.1,"B":0.1,"C":0,"D":0.1,"E":-1,"F":-1,"G":-1},
"D":{"A":0.1,"B":0.1,"C":0.1,"D":0,"E":-1,"F":-1,"G":-1},
"E":{"A":-1,"B":-1,"C":-1,"D":-1,"E":0,"F":0.4,"G":0.5},
"F":{"A":-1,"B":-1,"C":-1,"D":-1,"E":0.4,"F":0,"G":0.5},
"G":{"A":-1,"B":-1,"C":-1,"D":-1,"E":0.5,"F":0.5,"G":0}}

