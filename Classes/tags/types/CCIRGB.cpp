//
//  CCIRGB.cpp
//  CocosInterpreterTest
//
//  Created by Wu Tong on 13-4-10.
//
//

#include "CCIRGB.h"
NS_CC_EXT_BEGIN

CCIRGB::CCIRGB(CCIBufferReader *reader){
    this->Red = reader->readUI8();
    this->Green = reader->readUI8();
    this->Blue = reader->readUI8();
    this->Alpha = 0xff;
}
Color4B  CCIRGB::getColor(){
    return Color4B(this->Red, this->Green, this->Blue, this->Alpha);
}

NS_CC_EXT_END