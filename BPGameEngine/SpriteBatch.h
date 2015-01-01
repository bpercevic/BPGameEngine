//
//  SpriteBatch.h
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/31/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#ifndef __BPGameEngine__SpriteBatch__
#define __BPGameEngine__SpriteBatch__

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <vector>
#include "Vertex.h"
#include "glm/glm.hpp"

namespace BPGameEngine {
    
    enum class GlyphSortType {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE         // All same textures get drawn together
    };
    
    // A Single sprite. This struct is needed so we can sort our sprites by texture
    // Each texture gets its own draw call, we want to minimize texture switching.
    struct Glyph {
        GLuint texture;
        float depth;
        
        Vertex topLeft;
        Vertex botLeft;
        Vertex topRight;
        Vertex botRight;
    };
    
    class RenderBatch {
    public:
        RenderBatch(GLuint off, GLuint num, GLuint tex) : offset(off), numVertices(num), texture(tex) {};
        ~RenderBatch() {};
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };
    
    class SpriteBatch {
    public:
        SpriteBatch();
        ~SpriteBatch();
        
        void init();
        
        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);
        void end();
        
        void renderBatch();
        
    private:
        void _createRenderBatches();
        void _createVertexArray();
        void _sortGlyphs();
        
        static bool _compareFrontToBack(Glyph* a, Glyph* b);
        static bool _compareBackToFront(Glyph* a, Glyph* b);
        static bool _compareTexture(Glyph* a, Glyph* b);
        
        GLuint _vbo;
        GLuint _vao;
        std::vector<Glyph*> _glyphs;
        GlyphSortType _sortType;
        std::vector<RenderBatch> _renderBatches;
    };
}

#endif /* defined(__BPGameEngine__SpriteBatch__) */
