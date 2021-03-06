
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "../Map/Map.h"
#include "../../FrameWork/Sprite.h"
#include "../../FrameWork/SpriteManager.h"
#include "../../FrameWork/Scene/SceneManager.h"
#include "../../FrameWork/Animation.h"
#include"../../Object/Object/Bill.h"
#include "../../Object/BaseObject.h"
#include "../../Object/Enemies/Soldier.h"
#include "../IComponent.h"
#include "Scene.h"
<<<<<<< HEAD
#include "../../Object/Object/Bridge.h"
#include "../../Object/Enemies/WallTurret.h"
#include "../../Object/Enemies/Rifleman.h"
=======
#include "../../Bridge.h"
#include "../../WallTurret.h"
#include "../../Soldier.h"
#include "../../Rifleman.h"
#include "../../Cannon.h"
>>>>>>> origin/master

#define BOSS_VIEWPORT_ANCHOR		6112

using namespace std;
US_FRAMEWORK

ACTOR_SCENARIO
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;


	//void setViewport(Viewport* viewport);
	//static Viewport* getViewport();

	// Trả về một đối tượng theo id.
	// id: kiểu enum eID, định danh một đối tượng.
	// return: đối tượng cần tìm.
	BaseObject* getObject(eID id);
	BaseObject* getBill();
	BaseObject* _bulletmanager;
private:
	//void destroyobject();				// kiển tra nếu object hết hạn sử dụng thì phá huỷ đối tượng
	//Text* _text;

	//Help* _help;

	// Danh sách đối tượng dùng để tạo quadtree.
	//map <string, BaseObject*> _mapobject;

	// Danh sách các đối tượng hoạt động rộng không thể đưa vào quadtree.
	// (Ví dụ main character)
	vector<BaseObject*> _listobject;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*>   _active_object;

	vector<IControlable*> _listControlObject;
	Map* background;
	void updateViewport(BaseObject* objTracker);

	// quadtree
	//QNode* _root;
	// Trỏ đến bill, một số đối tượng cần truyền bill vào để xử lý, lấy ở đây.
	
//	BaseObject* _bulletmanager;
	BaseObject* _bill;
	//bool flagbossScenario;
	////ScenarioManager* _director;
	////ScenarioManager* _directorKillBoss;

	//void killbossScene_Bill(float deltatime, bool& isFinish);
	//void bossScene_Viewport(float dt, bool& finish);
	//void playPassBossSound(float dt, bool& finish);
	//void playBossStage1Sound(float dt, bool& finish);
	//// Xử lý kéo màn hình khi gặp bốt.
	//void ScenarioMoveViewport(float deltatime);
	//
	//// Xử lý thằng bill tự đi sau khi giết boss
	//void ScenarioKillBoss(float deltatime);

	//bool checkGameLife();

};

#endif // !__PLAY_SCENE_H__
