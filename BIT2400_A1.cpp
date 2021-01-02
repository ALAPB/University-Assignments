#include <iostream>
#include <assert.h>
#include <fstream>
#include <string.h>

using namespace std;

const unsigned int MAX_NUM_NODES = 20;

struct node
{
    //Variables made according to instructions on cuLearn
    
    //Id to identify a specific node
    unsigned int nodeID;

    //Array listing the nodeIDs connected to the node above
    //Using MAX_NUM_NODES as the max number for the sake of simplicity
    //If there was a limit to how many connections a node could have, I'd use it for a malloc
    unsigned int connectedNodes[MAX_NUM_NODES];

    //Number of connected nodes 
    int numConnected;

};

// Generate a node with no connections and an ID equal to id.
node createNode(unsigned int id)
{
    node createdNode;
    createdNode.nodeID = id;

    return createdNode;
}

// Helper function (you can define)
// Read in a series of numbers separated by tabs.
// and put those values in dstNumList
// The number of values read in is returned.
unsigned int readNumLine(char* toRead, unsigned int* dstNumList, unsigned int dstSize, bool firstLineRead)
{
    //Number of nodes found in the first line
    unsigned int numDstNodes = 0;

    //Pointer used to find the delimiters, in this case TAB
    char* delimPtr = strchr(toRead, '\t');

    //Pointer used to indicate the location of a node ID in the string
    char* nodePtr = delimPtr + 1;

    if (firstLineRead)
    {
        nodePtr = toRead;
    }

    //Loop runs as long as there are tabs left on the line
    while (delimPtr != NULL)
    {
        //Converting the node to an int, and storing it into the destination array
        dstNumList[numDstNodes] = atoi(nodePtr);

        //Looking for the next delimiter in the line
        delimPtr = strchr(nodePtr, '\t');

        //Moving over 1 space from the delimiter to get the node ID
        nodePtr = delimPtr + 1;

        //Adding 1 to the number of nodes for every loop that runs
        numDstNodes++;
    }



    return numDstNodes;
}


//isConnected takes in 2 node pointers, and checks whether they are connected or not
//By checking for destination node's ID in source node's connected node IDs
int isConnected(node* src, node* dst)
{
    //Loop checking the array of connected nodes
    for (int i = 0; i < src->numConnected; i++)
    {

        //Checking to see if dst is in the list of nodes connected to src
        if (src->connectedNodes[i] == dst->nodeID || dst->connectedNodes[i] == src->nodeID)
        {
            //Returning the index of the connected node in connectedNodes
            return i;

            /**
             For this assignment, we're assuming that if one node is connected to the other,
             then we assume the connection goes both ways.
             To confirm the connection goes both ways, I would add this code in this if statement:

             for(int j = 0; j < dst.numConnected; j++)
             {
                if(dst->connectedNodes[j] == src->nodeID)
                {
                    //Returns i because it's the original index of dst in src's array
                    return i;
                }
             }
            */

        }
    }

    //If the destination node wasn't connected, returns -1
    return -1;
}

// readNumNodes(char* firstLine) 
// takes first line of text is in the format "Nodes: # # # # # #"
// where the numbers are the node IDs (not in a particular order)
// and separated by a tab ('\t'). the destination array and array size
// are also passed as parameters. The destination array is then filled
// readNumNodes returns the number of nodes in the array.
unsigned int readNumNodes(char* firstLine, unsigned int* dstNodeList, unsigned int dstSize)
{
    // An assert makes sure that dstNodeList is not NULL.  If it is, the whole
    // program will stop (and you find the problem right away)
    assert(dstNodeList);
    
    bool firstRead = false;
    
    char* cPtr = strchr(firstLine, (int)':');
    cPtr += 1;
    return readNumLine(cPtr, dstNodeList, dstSize, firstRead);
}


/*
Partially GIVEN
Read in a text file representing the graph (like GraphFormat.txt).
Make nodes based on this file and presume the file is well formed
(ie things are written correctly)
Returns an array of nodes created and numNodesOut is changed to represent
the number of nodes read in
Parameters: fileName is the name (with path) of the text file being read in.
            numNodesOut is a pointer to an integer representing the number
            of nodes being read in. Note: this is how we work around functions
            only returning one value when we need them to return 2.
*/
node* readGraphFile(const char* fileName, int* numNodesOut)
{
    const int TXT_BUFF_SIZE = 50;
    char txtBuffer[TXT_BUFF_SIZE];
    unsigned int nodeIdxList[MAX_NUM_NODES];

    //Variable used in the readNumLine function to determine whether the first line was read or not
    bool firstLineRead = false;

    FILE* filePtr;
    fopen_s(&filePtr, fileName, "r");
    if (filePtr == NULL)
    {
        printf("File to read in does not exist it seems.");
        return NULL;
    }
    unsigned int numLines = 0;

    //Reading the first line in the text file
    char* textPtr = fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);
    numLines++;
    assert(textPtr);

    //Indicating that the first line was read
    firstLineRead = true;

    //Parsing the first line to determine the number of nodes
    int numNodes = readNumNodes(txtBuffer, nodeIdxList, MAX_NUM_NODES);

    //Allocating memory for the node array
    node* a_nodes = (node*)malloc(sizeof(node) * numNodes);
    
    for (int i = 0; i < numNodes; i++)
    {
        //Creating the nodes in the node array, assigning their nodeIDs
        a_nodes[i] = createNode(nodeIdxList[i]);
    }
    
    //Loop runs as many times as there are nodes
    for (int i = 0; i < numNodes; i++)
    {
        //Find the next line to read in the file
        textPtr = fgets(txtBuffer, TXT_BUFF_SIZE, filePtr);

        //Reads all the numbers in the line, and stores them in nodeIdxList 
        a_nodes[i].numConnected = readNumLine(txtBuffer, nodeIdxList, numNodes, firstLineRead);

        //After readNumLine fills nodeIdxList, the numbers are transfered into the node structures
        for (int j = 0; j < a_nodes[i].numConnected; j++)
        {   
            //Since the first number in a line represents the node ID
            //The first element in nodeIdxList is set to be a_nodes[i]'s nodeID
            if (j == 0)
            {
                a_nodes[i].nodeID = nodeIdxList[j];
            }
            //Any following entries in nodeIdxList are placed into a_node[i]'s connected nodes array
            else
            {
                a_nodes[i].connectedNodes[j - 1] = nodeIdxList[j];
            }
        }


        numLines++;
    }

    // TODO: update numNodesOut
    *numNodesOut = numNodes;

    fclose(filePtr);
    return a_nodes;
}

//Function I'm adding to print the data read in the file
void printFileContents(node* nodesToPrint, int numNodes)
{
    cout << "The following data has been found in the file:" << endl << endl;


    printf("ID | Connected Nodes\n");

    for (int i = 0; i < numNodes; i++)
    {
        cout << nodesToPrint[i].nodeID <<"  |  ";

        for (int j = 0; j < (nodesToPrint[i].numConnected - 1); j++)
        {
            cout << nodesToPrint[i].connectedNodes[j] << "    ";
        }
        cout << endl;
    }
    cout << endl;
}


//A function I added so the user could enter nodes and check whether they were connected or not
void userNodeCheck(node* myNodes, int numNodes)
{

    //Variable to store whether the nodes are connected or not
    int connectedStatus = -1;
    
    //Variable to store the user's selected source node
    int sourceID;

    //Variable to store the user's selected destination node
    int destID;

    cout << "Please enter a source node ID" << endl;
    cin >> sourceID;
    cout << "Please enter a destination node ID" << endl;
    cin >> destID;

    //Check the nodes for the source ID
    for (int i = 0; i < numNodes; i++)
    {
        if (myNodes[i].nodeID == sourceID)
        {
            //Check the nodes for the destination ID
            for (int j = 0; j < numNodes; j++)
            {

                if (myNodes[j].nodeID == destID)
                {
                    //If the destination ID matches one of the nodes, both source and destination nodes are sent to isConnected
                    connectedStatus = isConnected(&myNodes[i], &myNodes[j]);
                }
            }
        }
    }

    if (connectedStatus == -1)
    {
        cout << "Node " << sourceID << " is not connected to " << destID << endl;
    }
    else
    {
        cout << "Node " << sourceID << " is connected to " << destID << endl;
    }

    cout << "-----------------------------------" << endl;

}

int main()
{
    int numNodes = -1;

    /*
    Hardcoding two nodes to test isConnected
    sourceNode is connected to destNode, but destNode isn't connected to source node
    I set it up this way so that i could test both possibilities in isConnected
    */

    //node sourceNode = { 1, {2, 3, 4}, 3 };
    //node destNode = { 3, {6, 7, 8}, 3 };

    //Test that should find that the nodes are connected
    //isConnected(&sourceNode, &destNode);

    //Test that should find that the nodes are not connected
     //isConnected(&destNode, &sourceNode);

    node* myNodes = readGraphFile("GraphFormat.txt", &numNodes);

    printFileContents(myNodes, numNodes);

    if (numNodes > 0 && myNodes != NULL) {

        while (1)
        {
            //Function allowing the user to enter nodes they want to check
            userNodeCheck(myNodes, numNodes);
        }

        // Now release the dynamic array
        free(myNodes);
        myNodes = NULL;
    }
    return 0;
}
