#ifndef REMEMBER_H
#define REMEMBER_H

#include <vector>

// Define possible directions
typedef enum directionType 
{
    N = 0,  // Forward (relative to car)
    E = 1,  // Right
    S = 2,  // Backward  
    W = 3   // Left
} DirAvailable;

// Define memory entry
typedef struct nodeInformation
{
    bool availablePaths[4]; // Index corresponds to DirAvailable enum
    bool valid = true;
    int pathCount = 0;      // Number of available paths from this node
    int nodeId = -1;        // Unique identifier for this node
} nodeInfo;

class mapping {
private:
    std::vector<nodeInfo> memory;
    int ignoreUpdate = 0;           // Number of nodes to ignore when updating
    int currentNodeIndex = -1;      // Current position in memory
    int currentOrientation = N;  // DirAvailable currentOrientation;    // Current car orientation (absolute)
   


    void rotateMap();
    void markDeadEnd();
    DirAvailable rotateDirection(DirAvailable dir, int rotations) const;
    int countAvailablePaths(const nodeInfo& node) const;

public:
    // Record a new node with available paths (relative to car's current orientation)
    void recordNode(bool hasWest, bool hasEast, bool hasNorth, bool hasSouth = false);
    
    // Mark current path as dead end and calculate ignore distance
    void hitDeadEnd();
    
    // Navigate back to start/home position
    void returnHome();
    
    // Get current node information
    nodeInfo getCurrentNode() const;
    
    // Get total number of recorded nodes
    int getNodeCount() const { return memory.size(); }
    
    // Print memory state for debugging
    void printMemory() const;
    
    // Turn the car (updates orientation)
    void turnLeft();
    void turnRight();
    void turnAround();
};

#endif // REMEMBER_H