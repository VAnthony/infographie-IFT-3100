//
// Created by joffrey on 18-03-07.
//

#pragma once

#include <iostream>
#include "ofMain.h"

class Texture {
public:

    Texture();

    enum CompositionType {
        NONE, 
        ADD,
        AVG,
        SUB,
        MUL,
        DIFF,
        DARK,
        LIGHT,
    };

    enum FilterType {
        NONE_FILTER,
        EMBROSS,
        SHARPEN,
        EDGE_DETECT,
        BLUR,
        EDGE_ENFORCED,
        UNSHARP_MASKING,
    };

    void            loadImage(const ofImage *image);
    void            addComposition(const ofImage *image, CompositionType mode);
    void            setFilter(FilterType filter);
    /* const */           ofTexture &getTexture();
    void            compose();
    void            filter();
    void            applyModifier();

    map<std::string, FilterType > &getLabelFilter(void);


private:
    ofImage                     *image_;
    ofImage                     *composition_;
    ofImage                     render_;
    ofTexture                   texture_;
    CompositionType             selectedComposition_;
    FilterType                  selectedFilter_;

    const int                   kernel_size = 3;
    const int                   kernel_offset = kernel_size / 2;
    // int                   color_component_count = 3;

    map<FilterType, std::vector<std::vector<float> > > kernels_;
    map<std::string, FilterType > labelKernel_;
};