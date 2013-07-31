//
//  pgeRippleSprite.h
//  rippleDemo
//
//  Created by Lars Birkemose on 02/12/11.
//  Copyright 2011 Protec Electronics. All rights reserved.
//
// --------------------------------------------------------------------------
// import headers

#include "cocos2d.h"
#include <vector>

using namespace std;

// --------------------------------------------------------------------------
// defines

#define RIPPLE_DEFAULT_QUAD_COUNT_X             60
#define RIPPLE_DEFAULT_QUAD_COUNT_Y             40

#define RIPPLE_BASE_GAIN                        0.1f        // an internal constant

#define RIPPLE_DEFAULT_RADIUS                   100
#define RIPPLE_DEFAULT_RIPPLE_CYCLE             0.25f       // timing on ripple ( 1/frequenzy )
#define RIPPLE_DEFAULT_LIFESPAN                 1.4f        // entire ripple lifespan

// #define RIPPLE_BOUNCE                                       // makes ripples bounce off edges
#define RIPPLE_CHILD_MODIFIER                   2.0f        // strength modifier

// --------------------------------------------------------------------------
// typedefs

typedef enum {
    RIPPLE_TYPE_RUBBER,                                     // a soft rubber sheet
    RIPPLE_TYPE_GEL,                                        // high viscosity fluid
    RIPPLE_TYPE_WATER,                                      // low viscosity fluid
} RIPPLE_TYPE;

typedef enum {
    RIPPLE_CHILD_LEFT,
    RIPPLE_CHILD_TOP,
    RIPPLE_CHILD_RIGHT,
    RIPPLE_CHILD_BOTTOM,
    RIPPLE_CHILD_COUNT
} RIPPLE_CHILD;

USING_NS_CC;

typedef struct _rippleData {
    bool                    parent;                         // ripple is a parent
    bool                    childCreated[ 4 ];              // child created ( in the 4 direction )
    RIPPLE_TYPE             rippleType;                     // type of ripple ( se update: )
    CCPoint                 center;                         // ripple center ( but you just knew that, didn't you? )
    CCPoint                 centerCoordinate;               // ripple center in texture coordinates
    float                   radius;                         // radius at which ripple has faded 100%
    float                   strength;                       // ripple strength
    float                   runtime;                        // current run time
    float                   currentRadius;                  // current radius
    float                   rippleCycle;                    // ripple cycle timing
    float                   lifespan;                       // total life span
} rippleData;

// --------------------------------------------------------------------------
// interface

class pgeRippleSprite : public CCSprite, public CCTargetedTouchDelegate {
public:
   //static methods:
    static pgeRippleSprite* create(const char * filename);
    static pgeRippleSprite* create(CCRenderTexture* rtt, float scale);
    
    pgeRippleSprite();
    ~pgeRippleSprite();
    bool initWithFile(const char* filename);
    bool initWithRendertexture(CCRenderTexture* rtt, float scale);
    
    void tesselate();
    void addRipple(CCPoint pos, RIPPLE_TYPE type, float strength);
    void addRippleChild(rippleData* parent, RIPPLE_CHILD type);
    void update(float dt);
    CCTexture2D* spriteTexture();
    
    virtual void draw();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
private:
    bool isPointInsideSprite(CCPoint pos);
    bool isTouchInsideSprite(CCTouch* pTouch);
       
    CCTexture2D*            m_texture;
    int                     m_quadCountX;                   // quad count in x and y direction
    int                     m_quadCountY;
    int                     m_VerticesPrStrip;              // number of vertices in a strip
    int                     m_bufferSize;                   // vertice buffer size
    CCPoint*                m_vertice;                      // vertices
    CCPoint*                m_textureCoordinate;            // texture coordinates ( original )
    CCPoint*                m_rippleCoordinate;             // texture coordinates ( ripple corrected )
    bool*                   m_edgeVertice;                  // vertice is a border vertice
    vector<rippleData*>     m_rippleList;                   // list of running ripples
    
    
    CCPoint screenSize;
    float scaleRTT;
    float runTime;
};

