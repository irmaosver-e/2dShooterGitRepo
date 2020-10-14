#ifndef __Bullet_Handler__
#define __Bullet_Handler__

#include <vector>
#include <map>
#include "Singleton.h"
#include "Bullet.h"
#include "ObjectLayer.h"

struct FiringPoint
{
    Vector2Df position;
    std::string bulletType;
};

class BulletHandler : public Singleton<BulletHandler>
{
public:
    BulletHandler(token) {}
    ~BulletHandler() {}

    void registerBulletLayer(ObjectLayer* pBulletLayer) { m_bulletLayer = pBulletLayer; }
    void registerBulletType(std::string bulletType, LoaderParams& params);
    void registerFiringPoint(std::string firingObj, FiringPoint& firingPoint);

    LoaderParams* getBulletTypeParam(std::string bulletType);

    void fireBullet(std::string firingObj, Vector2Df firingObjPos, Vector2Df heading);

private:
    void addBullet(std::string bulletType);
    
    ObjectLayer* m_bulletLayer;

    std::map<std::string, LoaderParams> m_bulletTypes;
    std::map<std::string, FiringPoint> m_firingPoints;

};

typedef BulletHandler TheBulletHandler;

#endif /* defined ( __Bullet_Handler__ ) */
