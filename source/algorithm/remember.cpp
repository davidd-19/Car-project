// Implementation file (remember.cpp)
#include "algorithm/remember.h"
#include <iostream>
#include <algorithm>

void mapping::recordNode(bool hasWest, bool hasEast, bool hasNorth, bool hasSouth) {
    nodeInfo newNode;
    
    // Store paths relative to car's current orientation
    newNode.availablePaths[W] = hasWest;   // Left
    newNode.availablePaths[E] = hasEast;   // Right  
    newNode.availablePaths[N] = hasNorth;  // Forward
    newNode.availablePaths[S] = hasSouth;  // Backward
    
    newNode.pathCount = countAvailablePaths(newNode);
    newNode.nodeId = memory.size();
    
    // Only add if we're not in ignore mode or if this is a significant node
    if (ignoreUpdate <= 0 || newNode.pathCount > 2) {
        memory.push_back(newNode);
        currentNodeIndex = memory.size() - 1;
        
        // Reset ignore counter when we find a valid junction
        if (newNode.pathCount > 2) {
            ignoreUpdate = 0;
        }
    }
    
    // Decrement ignore counter
    if (ignoreUpdate > 0) {
        ignoreUpdate--;
    }
}

void mapping::hitDeadEnd() {
    if (currentNodeIndex >= 0 && currentNodeIndex < memory.size()) {
        // Mark current node as invalid
        memory[currentNodeIndex].valid = false;
        
        // Calculate distance back to last valid junction
        int distanceToValidPath = 0;
        for (int i = currentNodeIndex - 1; i >= 0; i--) {
            distanceToValidPath++;
            if (memory[i].valid && memory[i].pathCount > 1) {
                break; // Found a valid junction
            }
        }
        
        // Set ignore distance for future nodes
        ignoreUpdate = std::max(ignoreUpdate, distanceToValidPath);
        
        markDeadEnd();
    }
}

void mapping::markDeadEnd() {
    // Additional logic for handling dead ends
    // Could involve updating path availability in previous nodes
    if (currentNodeIndex > 0) {
        // Mark the path that led to this dead end as unavailable
        // This would require tracking which direction we came from
    }
}


void mapping::rotateMap() {
    // Rotate all stored directions when car changes orientation
    // This maintains the relative perspective where forward is always N
    for (auto& node : memory) {
        bool temp[4];
    
        for (int i = 0; i < 4; i++) {
            temp[i] = node.availablePaths[i];
        }
        
        // Rotate based on current orientation change
        // Implementation depends on how you want to handle absolute vs relative coordinates
    }
}


DirAvailable mapping::rotateDirection(DirAvailable dir, int rotations)const {
    // Rotate direction by specified number of 90-degree turns
    return static_cast<DirAvailable>((dir + rotations) % 4);
}

int mapping::countAvailablePaths(const nodeInfo& node) const {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (node.availablePaths[i]) {
            count++;
        }
    }
    /*for (bool path : node.availablePaths) {
        if (path) count++;
    }*/ 
    return count;
}

void mapping::turnLeft() {
    currentOrientation = rotateDirection(static_cast<DirAvailable>(currentOrientation), 3); // -1 mod 4 = 3
    // Optionally rotate the entire map to maintain relative perspective
}

void mapping::turnRight() {
    currentOrientation = rotateDirection(static_cast<DirAvailable>(currentOrientation), 1);
    // Optionally rotate the entire map to maintain relative perspective
}

void mapping::turnAround() {
    currentOrientation = rotateDirection(static_cast<DirAvailable>(currentOrientation), 2);
    // Optionally rotate the entire map to maintain relative perspective
}

void mapping::returnHome() {
    // Navigate back through recorded nodes to starting position
    // This could use the stored path information to find the optimal route
    currentNodeIndex = 0;
    ignoreUpdate = 0;
}

nodeInfo mapping::getCurrentNode() const {
    if (currentNodeIndex >= 0 && currentNodeIndex < memory.size()) {
        return memory[currentNodeIndex];
    }
    return nodeInfo(); // Return default node if invalid index
}

void mapping::printMemory() const {
    std::cout << "=== Memory State ===" << std::endl;
    for (size_t i = 0; i < memory.size(); i++) {
        const auto& node = memory[i];
        std::cout << "Node " << i << " (ID: " << node.nodeId << "): ";
        std::cout << "Paths: N=" << node.availablePaths[N] 
                  << " E=" << node.availablePaths[E]
                  << " S=" << node.availablePaths[S] 
                  << " W=" << node.availablePaths[W];
        std::cout << " Count=" << node.pathCount 
                  << " Valid=" << (node.valid ? "Yes" : "No") << std::endl;
    }
    std::cout << "Current Node: " << currentNodeIndex << std::endl;
    std::cout << "Ignore Update: " << ignoreUpdate << std::endl;
    std::cout << "Current Orientation: " << currentOrientation << " (0=N,1=E,2=S,3=W)" << std::endl;

}