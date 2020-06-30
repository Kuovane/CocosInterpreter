//
//  CCIDefineBitsJPEG3.cpp
//  CocosInterpreterTest
//
//  Created by Wu Tong on 13-4-9.
//
//

#include "CCIDefineBitsJPEG3.h"
#include "base/ZipUtils.h"

NS_CC_EXT_BEGIN
bool CCIDefineBitsJPEG3::initWithReader(cocos2d::extension::CCIBufferReader *reader, int tagType, int tagLength){
    
    CCIImageTag::initWithReader(reader, tagType, tagLength);
    
    this->alphaDataOffset = reader->readUI32();
    
    imageSize = this->alphaDataOffset;
    
    this->imageData = reader->readBytes(imageSize);
    
    
    this->bitmapAlphaData = reader->readBytes(tagLength-6-this->alphaDataOffset);
    
    this->loadImageData(imageData);
    
    delete this->imageData;
    delete this->bitmapAlphaData;
    
    return true;
}
void CCIDefineBitsJPEG3::loadImageData(UI8 * imageData){
    this->decodeInfo(imageData);
    
    int start = this->findJpegStart(imageData);
    
    imageData +=start;
    
    //Image::Format eImageFormat = Image::Format::UNKNOWN;
    Image image;
    image.initWithImageData(imageData, imageSize-start);
    
    if (tagLength-6-this->alphaDataOffset>0) {
        int length = this->width*this->height;
        UI8 * data = new UI8[length];
        int count = 0;
        count = ZipUtils::ccInflateMemoryWithHint(this->bitmapAlphaData, tagLength-6-this->alphaDataOffset, &data,length);
        
        UI8 * alphaData = new UI8[count];
        memcpy(alphaData,data,count);
        delete [] data;
        
        this->createTextureWithImageAndAlpha(&image,alphaData);
        delete[] alphaData;
    }
    
}
NS_CC_EXT_END