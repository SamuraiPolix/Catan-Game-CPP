#pragma once
#include <cstdlib>  // Include for size_t definition


namespace ariel{
    // enum of all resource types
    enum ResourceType {
        Ore = 1,
        Wheat = 2,
        Sheep = 3,
        Wood = 4,
        Brick = 5,
        Desert = 7      // not a resoure - tile type
    };

        enum VertexPosition {
        VERTEX_TOP_LEFT = 0,
        VERTEX_TOP = 1,
        VERTEX_TOP_RIGHT = 2,
        VERTEX_BOTTOM_RIGHT = 3,
        VERTEX_BOTTOM = 4,
        VERTEX_BOTTOM_LEFT = 5
    };

    enum EdgePosition {
        EDGE_TOP_LEFT = 0,
        EDGE_TOP_RIGHT = 1,
        EDGE_RIGHT = 2,
        EDGE_BOTTOM_RIGHT = 3,
        EDGE_BOTTOM_LEFT = 4,
        EDGE_LEFT = 5
    };

    // edgePosition + - operators override
    inline EdgePosition operator+(EdgePosition pos, int num){
        return (EdgePosition)(((int)(pos + num)) % 6);
    }
    inline EdgePosition operator+(int num, EdgePosition pos){
        return (EdgePosition)(((int)(pos + num)) % 6);
    }
    inline EdgePosition operator-(EdgePosition pos, int num){
        return (EdgePosition)(((int)(pos-num)) % 6);
    }
    inline EdgePosition operator-(int num, EdgePosition pos){
        return (EdgePosition)(((int)(num - pos)) % 6);
    }
    inline VertexPosition operator+(VertexPosition pos, int num){
        return (VertexPosition)(((int)(pos + num)) % 6);
    }
    inline VertexPosition operator+(int num, VertexPosition pos){
        return (VertexPosition)(((int)(pos + num)) % 6);
    }
    inline VertexPosition operator-(VertexPosition pos, int num){
        return (VertexPosition)(((int)(pos - num)) % 6);
    }
    inline VertexPosition operator-(int num, VertexPosition pos){
        return (VertexPosition)(((int)(num - pos)) % 6);
    }


    // EdgePosition operator+(EdgePosition pos, size_t num){
    //     return (EdgePosition)(((size_t)(pos + num)) % 6);
    // }
    // EdgePosition operator+(size_t num, EdgePosition pos){
    //     return (EdgePosition)(((size_t)(pos + num)) % 6);
    // }
    // EdgePosition operator-(EdgePosition pos, size_t num){
    //     return (EdgePosition)(((size_t)(pos-num)) % 6);
    // }
    // EdgePosition operator-(size_t num, EdgePosition pos){
    //     return (EdgePosition)(((size_t)(num - pos)) % 6);
    // }
    // VertexPosition operator+(VertexPosition pos, size_t num){
    //     return (VertexPosition)(((size_t)(pos + num)) % 6);
    // }
    // VertexPosition operator+(size_t num, VertexPosition pos){
    //     return (VertexPosition)(((size_t)(pos + num)) % 6);
    // }
    // VertexPosition operator-(VertexPosition pos, size_t num){
    //     return (VertexPosition)(((size_t)(pos - num)) % 6);
    // }
    // VertexPosition operator-(size_t num, VertexPosition pos){
    //     return (VertexPosition)(((size_t)(num - pos)) % 6);
    // }
}