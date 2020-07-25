#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
	
}


playGround::~playGround()
{
}

//초기화 함수
HRESULT playGround::init()
{
	gameNode::init(true);
	imageLoad();
	soundLoad();
	_stageManager = new stageManager;
	_stageManager->init();

	return S_OK;
}

//메모리 해제
void playGround::release()
{
	_stageManager->release();
}

//연산
void playGround::update()
{
	gameNode::update();

	CAMERAMANAGER->update();
	_stageManager->update();

	if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		SOUNDMANAGER->play("girlHit", 1.0f);
	}
}

//그리기 전용
void playGround::render()
{	
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//=================================================



	_stageManager->render();

	
	TIMEMANAGER->render(getMemDC());
	//=============================================
	_backBuffer->render(getHDC(), 0, 0);
}

void playGround::imageLoad()
{
	// ======= UI
	IMAGEMANAGER->addImage("s_boss_name", "image/ui/small_boss_name.bmp", 143, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("s_kyoko_name", "image/ui/small_kyoyo_name.bmp", 143, 38, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("s_misako_name", "image/ui/small_misako_name.bmp", 143, 38, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("kyoko_img", "image/ui/kyoko_img.bmp", 600, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("misuzu_img", "image/ui/misuzu_img.bmp", 600, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("misako_img", "image/ui/misako_img.bmp", 600, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("letter_box", "image/ui/UI_footer.bmp", 1600, 100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("character_hud", "image/ui/UI_RCG_HUD_portrait_Kyoko_default.bmp", 150, 169, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud", "image/ui/NULL_UHD_BAR2.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("status_hud_back", "image/ui/NULL_UHD_BAR.bmp", 414, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title_background", "image/ui/titleBackGround.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("coin_ui", "image/ui/coin.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("phone_ui", "image/ui/Phone.bmp", 463, 800, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("phone_active", "image/ui/phone_active.bmp", 1600, 900, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select_item", "image/ui/select_item.bmp", 63, 61, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("equip_select", "image/ui/equip_select.bmp", 42, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("loading_sprite", "image/ui/loadingSprite4x1.bmp", 1152, 227, 4, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("select_arrow", "image/ui/select_arrow.bmp", 66, 76, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("full_hd", "image/ui/hpBar.bmp", 389, 21, true, RGB(255, 0, 255));
	// ======= UI

	// ======= player

	IMAGEMANAGER->addImage("backGround", "image/map/01_Detention_BG_x3_start.bmp", 2395, 1100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel1", "image/map/01_Detention_BG_x3_second.bmp", 2395, 1100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("pixel2", "image/map/01_Detention_BG_x3_start_second.bmp", 2395, 1100, false, RGB(0, 0, 0));

	IMAGEMANAGER->addFrameImage("PLAYER_IDLE", "image/player/Kyoko_Idle.bmp", 1440, 450, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_WALK", "image/player/Kyoko_Walk.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_RUN", "image/player/Kyoko_Run.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_JUMP", "image/player/Kyoko_Jump.bmp", 405, 414, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK1", "image/player/Kyoko_ComboAttack1.bmp", 1548, 462, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK2", "image/player/Kyoko_ComboAttack2.bmp", 1869, 452, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_ATTACK3", "image/player/Kyoko_ComboAttack3.bmp", 2970, 462, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_DIVE", "image/player/Kyoko_Dive.bmp", 5040, 456, 21, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_START", "image/player/Kyoko_BattleStart.bmp", 2964, 420, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_DOWN", "image/player/Kyoko_Down.bmp", 4896, 457, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_OVER", "image/player/Kyoko_GameOver.bmp", 6240, 477, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_GUARD", "image/player/Kyoko_Guard.bmp", 351, 464, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_HIT", "image/player/Kyoko_Hit.bmp", 246, 456, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STAND_UP", "image/player/Kyoko_StandUp.bmp", 3315, 452, 17, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STOMP", "image/player/Kyoko_Stomp.bmp", 1290, 451, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STUNNED", "image/player/Kyoko_Stunned.bmp", 384, 384, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_KICK", "image/player/Kyoko_HurricaneKick.bmp", 2997, 657, 9, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("PLAYER_STRONG", "image/player/player_strongAttack.bmp", 3030, 560, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PLAYER_SHADOW", "image/player/Kyoko_Shadow.bmp", 128, 38, true, RGB(255, 0, 255));

	// ======= player

	IMAGEMANAGER->addImage("stage2", "image/map/stage2.bmp", 4000, 1200, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("stage2pixel", "image/map/stage2pixel.bmp", 4000, 1200, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("stage1", "image/map/stage.bmp", 2395, 1100, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("금동전", "image/item/금동전.bmp", 36, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("은동전", "image/item/은동전.bmp", 36, 37, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물약1", "image/item/물약1.bmp", 70, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("물약2", "image/item/물약2.bmp", 70, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기둥좌", "image/obstacle/기둥좌.bmp", 200, 880, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("기둥우", "image/obstacle/기둥우.bmp", 200, 880, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("책상", "image/obstacle/책상.bmp", 195, 215, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("팬츠", "image/item/팬츠.bmp", 110, 115, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("흉기", "image/item/흉기.bmp", 110, 115, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("자판기", "image/obstacle/자판기.bmp", 700, 346, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "image/map/01_Detention_BG_x3_start_second.bmp", 2395, 1100, false, RGB(0, 0, 0));



	// ======= 보스
	IMAGEMANAGER->addImage("보스배경", "image/map/bossMap1.bmp", 2538, 1200, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스배경pixel", "image/map/bossMap1_collision.bmp", 2538, 1200, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("보스그림자", "image/boss/boss_shadow.bmp", 153, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_idle", "image/boss/boss_idle.bmp", 2844, 582, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit", "image/boss/boss_hit.bmp", 9300, 576, 31, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_hit_getup", "image/boss/boss_hit_getup.bmp", 3915, 552, 15, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_jumpAttack", "image/boss/boss_jumpAttack.bmp", 5832, 618, 24, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_walk", "image/boss/boss_walk.bmp", 1770, 552, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_death", "image/boss/boss_death.bmp", 4329, 540, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_attack_elbow", "image/boss/boss_attack_elbow.bmp", 2739, 600, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_angry", "image/boss/boss_angry.bmp", 3840, 534, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_attack", "image/boss/boss_attack.bmp", 4788, 534, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_dash", "image/boss/boss_dash.bmp", 3276, 528, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_heavyAttack", "image/boss/boss_heavyAttack.bmp", 10452, 546, 26, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_block", "image/boss/boss_block.bmp", 744, 528, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_roar", "image/boss/boss_roar.bmp", 2592, 534, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss_taunt", "image/boss/boss_taunt.bmp", 5016, 690, 22, 2, true, RGB(255, 0, 255));


	// ========== 적
	IMAGEMANAGER->addImage("enemy_shadow", "image/enemy/enemy_shadow.bmp", 128, 38, true, RGB(255, 0, 255));
	//=======================남자애=======================//
	IMAGEMANAGER->addFrameImage("boy_idle", "image/enemy/boy_idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_walk", "image/enemy/boy_walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_run", "image/enemy/boy_run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack1", "image/enemy/boy_attack1.bmp", 1764, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack2", "image/enemy/boy_attack2.bmp", 1386, 510, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_attack3", "image/enemy/boy_attack3.bmp", 1863, 558, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_sidekick", "image/enemy/boy_sidekick.bmp", 1764, 444, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit1", "image/enemy/boy_hit1.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit2", "image/enemy/boy_hit2.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_hit3", "image/enemy/boy_hit3.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_groundhit", "image/enemy/boy_groundhit.bmp", 1100, 420, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_knockdown", "image/enemy/boy_knockdown.bmp", 8910, 420, 33, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boy_dizzy", "image/enemy/boy_dizzy.bmp", 633, 408, 4, 2, true, RGB(255, 0, 255));
	//=======================여자애=======================//
	IMAGEMANAGER->addFrameImage("girl_idle", "image/enemy/girl_idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_walk", "image/enemy/girl_walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_run", "image/enemy/girl_run.bmp", 1470, 330, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_jump", "image/enemy/girl_jump.bmp", 333, 366, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack1", "image/enemy/girl_attack1.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack2", "image/enemy/girl_attack2.bmp", 1197, 357, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_attack3", "image/enemy/girl_attack3.bmp", 2412, 414, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit1", "image/enemy/girl_hit1.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit2", "image/enemy/girl_hit2.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_hit3", "image/enemy/girl_hit3.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_groundhit", "image/enemy/girl_groundhit.bmp", 900, 360, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_knockdown", "image/enemy/girl_knockdown.bmp", 7425, 360, 33, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("girl_dizzy", "image/enemy/girl_dizzy.bmp", 456, 324, 4, 2, true, RGB(255, 0, 255));
	//=======================치어리더=======================//
	IMAGEMANAGER->addFrameImage("cheer_idle", "image/enemy/cheer_idle.bmp", 1980, 432, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_walk", "image/enemy/cheer_walk.bmp", 2736, 438, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_run", "image/enemy/cheer_run.bmp", 1368, 318, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_jump", "image/enemy/cheer_jump.bmp", 540, 474, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_attack1", "image/enemy/cheer_attack1.bmp", 1332, 468, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_attack2", "image/enemy/cheer_attack2.bmp", 1827, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_attack3", "image/enemy/cheer_attack3.bmp", 3700, 408, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_hit1", "image/enemy/cheer_hit1.bmp", 513, 426, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_hit2", "image/enemy/cheer_hit2.bmp", 513, 426, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_hit3", "image/enemy/cheer_hit3.bmp", 513, 426, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_knockdown", "image/enemy/cheer_knockdown.bmp", 8415, 414, 33, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_dizzy", "image/enemy/cheer_dizzy.bmp", 540, 390, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("cheer_flip", "image/enemy/cheer_backflip.bmp", 6732, 612, 22, 2, true, RGB(255, 0, 255));

	// ========== effect
	IMAGEMANAGER->addFrameImage("hit_effect", "image/effect/hit.bmp", 384, 96, 4, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("hit_effect", "hit_effect", 384, 96, 96, 96, 1, 0.2f, 10);

	IMAGEMANAGER->addFrameImage("e_hit_effect", "image/effect/et_boom_big.bmp", 960, 89, 10, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("e_hit_effect", "e_hit_effect", 960, 89, 96, 89, 1, 0.7f, 10);

	IMAGEMANAGER->addFrameImage("boss_heavyAttack_effect", "image/effect/superTackle.bmp", 160, 74, 4, 1, true, RGB(255, 0, 255));
	EFFECTMANAGER->addEffect("boss_heavyAttack_effect", "boss_heavyAttack_effect", 160, 74, 40, 74, 1, 0.7f, 10);

}

void playGround::soundLoad()
{
	SOUNDMANAGER->addSound("배경음", "mp3/리버시티걸즈-배경음.mp3", true, false);
	SOUNDMANAGER->addSound("money", "mp3/돈소리.mp3", false, false);
	SOUNDMANAGER->addSound("발차기스윙", "mp3/플레발차기스윙.wav", false, false);
	SOUNDMANAGER->addSound("inventory", "mp3/인벤토리창.mp3", false, false);
	SOUNDMANAGER->addSound("vending", "mp3/자판기.wav", false, false);
	SOUNDMANAGER->addSound("플레점프", "mp3/플레점프.mp3", false, false);
	SOUNDMANAGER->addSound("플레1타", "mp3/플레1타.mp3", false, false);
	SOUNDMANAGER->addSound("플레q공격", "mp3/플레q공격.mp3", false, false);
	SOUNDMANAGER->addSound("플레히트", "mp3/플레히트.mp3", false, false);
	SOUNDMANAGER->addSound("플레밟기", "mp3/플레밟기.wav", false, false);
	SOUNDMANAGER->addSound("플레맞기", "mp3/플레맞기.mp3", false, false);
	SOUNDMANAGER->addSound("플레슬라이딩펀치", "mp3/플레슬라이딩펀치.wav", false, false);
	SOUNDMANAGER->addSound("gameStart", "mp3/게임시작.wav", false, false);
	SOUNDMANAGER->addSound("gameOver", "mp3/게임오버.wav", false, false);
	SOUNDMANAGER->addSound("보스내려찍기", "mp3/보스내려찍기.wav", false, false);
	SOUNDMANAGER->addSound("boyHit", "mp3/남자히트.wav", false, false);
	SOUNDMANAGER->addSound("girlHit", "mp3/여자히트.wav", false, false);
	SOUNDMANAGER->addSound("보스강펀치", "mp3/보스강펀치.wav", false, false);
	SOUNDMANAGER->addSound("보스박치기", "mp3/보스박치기.wav", false, false);
	SOUNDMANAGER->addSound("보스뺨갈기기", "mp3/보스뺨갈기기.wav", false, false);
	SOUNDMANAGER->addSound("보스점프엉덩방아", "mp3/보스점프엉덩방아.wav", false, false);
	SOUNDMANAGER->addSound("보스점프", "mp3/보스점프.wav", false, false);
	SOUNDMANAGER->addSound("보스분노", "mp3/보스분노.wav", false, false);
	SOUNDMANAGER->addSound("보스땅바닥", "mp3/보스땅바닥.wav", false, false);
	SOUNDMANAGER->addSound("item", "mp3/아이템획득.mp3", false, false);
	SOUNDMANAGER->addSound("inventorySelect", "mp3/인벤토리선택.wav", false, false);
	SOUNDMANAGER->addSound("informationSelect", "mp3/정보선택.mp3", false, false);
	SOUNDMANAGER->addSound("select", "mp3/선택.mp3", false, false);
	SOUNDMANAGER->addSound("init", "mp3/init.mp3", false, false);
	SOUNDMANAGER->addSound("communication", "mp3/대화.mp3", false, false);
	SOUNDMANAGER->addSound("itemUse", "mp3/아이템사용.wav", false, false);


	SOUNDMANAGER->play("배경음", 0.1f);
}
