#ifndef KS_HEXAGON_H
#define KS_HEXAGON_H

#include <ks/base/ksBase.h>


class kswht12102 : public ksBase
{
public:
    kswht12102();
    ~kswht12102();
    
    virtual void init();
    
    virtual void draw(int x, int y, int w, int h );
    
    virtual void update(float dt);
    
private:
    
    ofMesh HexagonMesh;
    ofFbo F;
    float T;
    
};

#endif

