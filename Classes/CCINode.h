//
//  CCINode.h
//  CocosInterpreterTest
//
//  Created by Wu Tong on 13-4-7.
//
//

#ifndef __CocosInterpreter__CCINode__
#define __CocosInterpreter__CCINode__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCIMovie.h"
#include "deprecated/CCDictionary.h"
#include "CCIFillStyleArray.h"

#include "CCICxformWithAlpha.h"

NS_CC_EXT_BEGIN

/**
 * Data source that governs table backend data.
 */
class CCINodeFrameDelegate
{
public:
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    virtual void didEnterFrame(int frameIndex,std::string frameLabel) = 0;
    
};





class CCINode:public Node{
private:
    CCINode();
    virtual ~CCINode();
    float frameRate;
    int frameCount;
    bool initWithFile(std::string cci_filename);
    
    void showFrame(float dt);
    
    CCIMovie * swfMovie;
    std::vector<CCIMovieTag *> tags;
    
    __Dictionary * textures;
    __Dictionary * nodes;
    int currentTag = 0;
    int currentFrame = 1;
    
    bool isPlayingFrameLabel = false;
    int  frameLabelIndex = 0;
    std::string frameLabel = "";
    bool isPlaying;
    
    CCINodeFrameDelegate * delegate = NULL;
    
    static CCINode* createWithTags(std::vector<CCIMovieTag *> tags,CCIMovie * swfMovie,__Dictionary * nodes);
    bool initWithTags(std::vector<CCIMovieTag *> tags,CCIMovie * swfMovie,__Dictionary * nodes);
    
    void applyColorTransform(CCNode * node,Color4B colorTransform);
    void applySkew(CCNode * node,float skewX,float skewY,bool isInner);

public:
    static CCINode* create(std::string cci_filename);
    //play anyway
    void play();
    void stop();
    
    void gotoAndPlay(std::string frameFlag);

    float getFrameRate();
    void setFrameRate(float frameRate);
    
    
    void setFlipX(bool flipX);
    void setFlipY(bool flipY);
    void setResize(float resize);
    virtual void setScaleX(float scaleX);
    virtual void setScaleY(float scaleY);
    void setScale(float scale);
    virtual float getScaleX();
    virtual float getScaleY();
    float getScale();
    
    void setDelegate(CCINodeFrameDelegate * delegate);
    CCINodeFrameDelegate * getDelegate();
private:
    void fillNodeWithStyle(CCIFillStyleArray * fillStyles,CCNode * node,CCIRect * nodeBounds);
    void loadImages();
    
    float resize = 1.0;
    bool  flipX = false;
    bool  flipY = false;
    
    float originalScaleX = 1.0;
    float originalScaleY = 1.0;
};

NS_CC_EXT_END

#endif /* defined(__CocosInterpreterTest__CCINode__) */
