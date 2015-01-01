//
//  SpriteBatch.cpp
//  BPGameEngine
//
//  Created by Bojan Percevic on 12/31/14.
//  Copyright (c) 2014 Bojan Percevic. All rights reserved.
//

#include "SpriteBatch.h"

namespace BPGameEngine {
    
#pragma mark - SpriteBatch
    SpriteBatch::SpriteBatch() :
        _vbo(0),
        _vao(0)
    {
    
    }

    SpriteBatch::~SpriteBatch() {
        
    }
    
    void SpriteBatch::init() {
        _createVertexArray();
    }
    
    void SpriteBatch::begin(GlyphSortType sortType /* = GlyphSortType::TEXTURE */) {
        // Figure out how we want to sort the sprites
        _sortType = sortType;
        _renderBatches.clear(); // changes size of vector back to 0
        
        for (int i = 0; i < _glyphs.size(); i++) {
            delete _glyphs[i];
        }
        _glyphs.clear();
    }
    
    void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color) {
        Glyph* glyph = new Glyph;
        glyph->texture = texture;
        glyph->depth = depth;
        
        glyph->topLeft.color = color;
        glyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        glyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
        
        glyph->botLeft.color = color;
        glyph->botLeft.setPosition(destRect.x, destRect.y);
        glyph->botLeft.setUV(uvRect.x, uvRect.y);
        
        glyph->botRight.color = color;
        glyph->botRight.setPosition(destRect.x + destRect.z, destRect.y);
        glyph->botRight.setUV(uvRect.x + uvRect.z, uvRect.y);
        
        glyph->topRight.color = color;
        glyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        glyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
        
        _glyphs.push_back(glyph);
        //        delete glyph; // will be deleted on begin()
    }
    
    void SpriteBatch::end() {
        _sortGlyphs();
        _createRenderBatches();
    }
    
    void SpriteBatch::renderBatch() {
        glBindVertexArray(_vao);
        for (int i = 0; i < _renderBatches.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
            glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
        }
        glBindVertexArray(0);
    }
    
#pragma mark - Private
    void SpriteBatch::_createRenderBatches() {
        if (_glyphs.empty()) {
            return;
        }
        
        // loop through glyphs, for each glyph add to batch
        // for each glyph with a new texture, make a new batch
        
        // make batch and copy it to vector
//        RenderBatch batch(0, 6, _glyphs[0]->texture);
//        _renderBatches.push_back(batch);
        
        // instead, we'll emplace_back which allows us to skip creating a batch var
        // up front and instead we just pass the constructor vars
        
        std::vector<Vertex> vertices;
        vertices.resize(_glyphs.size() * 6);
        
        _renderBatches.emplace_back(0, 6, _glyphs[0]->texture);
        
        int offset = 0;
        
        int currentVertex = 0;
        vertices[currentVertex++] = _glyphs[0]->topLeft;
        vertices[currentVertex++] = _glyphs[0]->botLeft;
        vertices[currentVertex++] = _glyphs[0]->botRight;
        vertices[currentVertex++] = _glyphs[0]->botRight;
        vertices[currentVertex++] = _glyphs[0]->topRight;
        vertices[currentVertex++] = _glyphs[0]->topLeft;
        offset += 6;
        

        for (int currentGlyph = 1; currentGlyph < _glyphs.size(); currentGlyph++) {
            if (_glyphs[currentGlyph]->texture != _glyphs[currentGlyph - 1]->texture) {
                _renderBatches.emplace_back(offset, 6, _glyphs[currentGlyph]->texture);
            } else {
                _renderBatches.back().numVertices += 6;
            }
            
            vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
            vertices[currentVertex++] = _glyphs[currentGlyph]->botLeft;
            vertices[currentVertex++] = _glyphs[currentGlyph]->botRight;
            vertices[currentVertex++] = _glyphs[currentGlyph]->botRight;
            vertices[currentVertex++] = _glyphs[currentGlyph]->topRight;
            vertices[currentVertex++] = _glyphs[currentGlyph]->topLeft;
            offset += 6;
        }
        
        // upload data to vbo
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        // We might already have data in this buffer
        // glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
        
        // So we "orphan" the buffer, we tell it to bind nullptr which deletes it
        // faster than rewriting the buffer with new data
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        
        // Then we upload the new data
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), &vertices[0]);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
    }
    
    void SpriteBatch::_createVertexArray() {
        // VAO encapsulates all state we need to render.
        // VAO and VBO
        if (!_vao) {
            glGenVertexArrays(1, &_vao);
        }
        
        // Generate vertex buffer
        if (!_vbo) {
            glGenBuffers(1, &_vbo);
        }
        
        // Bind VAO then VBO
        glBindVertexArray(_vao);
        
        // Now whenever we bind the VAO, we dont have to bind the VBO. (automatic)
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        
        // Enable attributes and describe them
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        
        glBindVertexArray(0);
    }
    
    void SpriteBatch::_sortGlyphs() {
        switch (_sortType) {
            case GlyphSortType::FRONT_TO_BACK:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareFrontToBack);
                break;
            case GlyphSortType::BACK_TO_FRONT:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareBackToFront);
                break;
            case GlyphSortType::TEXTURE:
                std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareTexture);
                break;
                
            default:
                break;
        }
    }
    
#pragma mark - Sorting functions
    bool SpriteBatch::_compareFrontToBack(Glyph* a, Glyph* b) {
        return a->depth < b->depth;
    }
    
    bool SpriteBatch::_compareBackToFront(Glyph* a, Glyph* b) {
        return a->depth > b->depth;
    }
    bool SpriteBatch::_compareTexture(Glyph* a, Glyph* b) {
        return a->texture < b->texture;
    }
    
}