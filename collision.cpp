/*======================================================================================//
*  ・当たり判定の処理
*
//======================================================================================*/
#include "collision.h"
#include "main.h"
#include "field.h"
#include "item.h"
#include "explosion.h"
#include "goal.h"
#include "moveField.h" 
#include "fieldDis.h"

// プレイヤーキャラクターと敵キャラクターの当たり判定
// プレイヤーから呼び出す関数
//

bool PlayerCollisionEnemy(PLAYER* player)
{
	// キャラクターの矩形を作成
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;

	// 敵キャラクターの構造体ポインターを取得
	ENEMY* enemyArray = GetENEMY();
	// すべての構造体配列をチェック
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		if (enemyArray[cnt].use == false)
		{ // 配列の敵の情報が有効ではない
			continue;
		}

		// 敵キャラクターの矩形を作成
		float enemyLeft = enemyArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float enemyRight = enemyArray[cnt].pos.x + CHARACTER_COLLISION_SIZEX;
		float enemyUp = enemyArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float enemyDown = enemyArray[cnt].pos.y + CHARACTER_COLLISION_SIZEY;

		// 当たり判定
		if (playerRight < enemyLeft)
		{ // プレイヤーの右側より奥に敵がいる
			continue;
		}
		if (playerLeft > enemyRight)
		{ // プレイヤーの左側より奥に敵がいる
			continue;
		}
		if (playerDown < enemyUp)
		{ // プレイヤーの下側より奥敵がいる
			continue;
		}
		if (playerUp > enemyDown)
		{ // プレイヤーの上側より奥に敵がいる
			continue;
		}
		return true;

	}


	// どの弾ともあたってない
	return false;
}

// 壁との当たり判定
// プレイヤーから呼び出す関数
// 戻り値 true : 当たり false : 外れ
bool PlayerCollisionWall(PLAYER* player)
{
	// キャラクターの矩形を作成
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;
	FIELD* fieldArray = GetField();
	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (fieldArray[cnt].bUse == false)
		{// 配列の敵の情報が有効でない
			continue; // 当たらない
		}

		// 障害物の矩形を作成
		/*float fieldLeft = fieldArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float fieldRight = fieldArray[cnt].pos.x + fieldArray[cnt].scl.width - CHARACTER_COLLISION_SIZEX;
		float fieldUp = fieldArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float fieldDown = fieldArray[cnt].pos.y + fieldArray[cnt].scl.height - CHARACTER_COLLISION_SIZEY;*/

		float fieldLeft = fieldArray[cnt].pos.x;
		float fieldRight = fieldArray[cnt].pos.x + fieldArray[cnt].scl.width;
		float fieldUp = fieldArray[cnt].pos.y;
		float fieldDown = fieldArray[cnt].pos.y + fieldArray[cnt].scl.height;

		// 当たり判定
		if (playerRight < fieldLeft)
		{// プレイヤーの右側より奥に障害物がいる
			continue; // 当たらない
		}
		if (playerLeft > fieldRight)
		{// プレイヤーの左側より奥に障害物がいる
			continue;
		}
		if (playerUp > fieldDown)
		{// プレイヤーの上側より奥に障害物がいる
			continue;
		}
		if (playerDown < fieldUp)
		{// プレイヤーの下側より奥に障害物がいる
			continue;
		}
		return true;
	}
	// どの障害物とも当たっていない
	return false;
}
// 壁との当たり判定
// 敵から呼び出す関数
// 戻り値 true : 当たり false : 外れ
bool EnemyCollisionWall(ENEMY* enemy)
{
	// 敵の矩形を作成
	float enemyLeft = enemy->pos.x - CHARACTER_COLLISION_SIZEX;
	float enemyRight = enemy->pos.x + CHARACTER_COLLISION_SIZEX;
	float enemyUp = enemy->pos.y - CHARACTER_COLLISION_SIZEY;
	float enemyDown = enemy->pos.y + CHARACTER_COLLISION_SIZEY;
	FIELD* fieldArray = GetField();
	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (fieldArray[cnt].bUse == false)
		{// 配列の障害物の情報が有効でない
			continue; // 当たらない
		}

		// 障害物の矩形を作成
		float fieldLeft = fieldArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float fieldRight = fieldArray[cnt].pos.x + fieldArray[cnt].scl.width - CHARACTER_COLLISION_SIZEX;
		float fieldUp = fieldArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float fieldDown = fieldArray[cnt].pos.y + fieldArray[cnt].scl.height - CHARACTER_COLLISION_SIZEY;

		// 当たり判定
		if (enemyRight < fieldLeft)
		{// プレイヤーの右側より奥に障害物がいる
			continue; // 当たらない
		}
		if (enemyLeft > fieldRight)
		{// プレイヤーの左側より奥に障害物がいる
			continue;
		}
		if (enemyUp > fieldDown)
		{// プレイヤーの上側より奥に障害物がいる
			continue;
		}
		if (enemyDown < fieldUp)
		{// プレイヤーの下側より奥に障害物がいる
			continue;
		}
		return true;
	}
	// どの障害物とも当たっていない
	return false;
}
// 壁との当たり判定
// 敵から呼び出す関数
// 戻り値 true : 当たり false : 外れ
bool BulletCollisionWall(BULLET* bullet)
{
	// 敵の矩形を作成
	float bulletLeft = bullet->pos.x - CHARACTER_COLLISION_SIZEX;
	float bulletRight = bullet->pos.x + CHARACTER_COLLISION_SIZEX;
	float bulletUp = bullet->pos.y - CHARACTER_COLLISION_SIZEY;
	float bulletDown = bullet->pos.y + CHARACTER_COLLISION_SIZEY;
	FIELD* fieldArray = GetField();
	for (int cnt = 0; cnt < FIELD_MAX; cnt++)
	{
		if (fieldArray[cnt].bUse == false)
		{// 配列の障害物の情報が有効でない
			continue; // 当たらない
		}

		// 障害物の矩形を作成
		float fieldLeft = fieldArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float fieldRight = fieldArray[cnt].pos.x + fieldArray[cnt].scl.width - CHARACTER_COLLISION_SIZEX;
		float fieldUp = fieldArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float fieldDown = fieldArray[cnt].pos.y + fieldArray[cnt].scl.height - CHARACTER_COLLISION_SIZEY;

		


		// 当たり判定
		if (bulletRight < fieldLeft)
		{// プレイヤーの右側より奥に障害物がいる
			continue; // 当たらない
		}
		if (bulletLeft > fieldRight)
		{// プレイヤーの左側より奥に障害物がいる
			continue;
		}
		if (bulletUp > fieldDown)
		{// プレイヤーの上側より奥に障害物がいる
			continue;
		}
		if (bulletDown < fieldUp)
		{// プレイヤーの下側より奥に障害物がいる
			continue;
		}
		return true;
		// 弾と敵が当たった
		RemoveBullet(cnt);
		CreateExplosion(bullet[cnt].pos, 0);
	}
	// どの障害物とも当たっていない
	return false;
}

bool EnemyCollisionBullet(ENEMY* enemy)
{ // 敵の判定用の四角形を作成
	float enemyLeft = enemy->pos.x - CHARACTER_COLLISION_SIZEX;
	float enemyRight = enemy->pos.x + CHARACTER_COLLISION_SIZEX;
	float enemyUp = enemy->pos.y - CHARACTER_COLLISION_SIZEY;
	float enemyDown = enemy->pos.y + CHARACTER_COLLISION_SIZEY;
	// 弾の配列ポインター取得
	BULLET* bullet = GetBullet();
	// 全ての弾とのチェック
	for (int cnt = 0; cnt < BULLET_MAX; cnt++)
	{// 構造体が使用中か
		if (bullet[cnt].use == true)
		{// 弾の判定用の四角形を作成
			float bulletLeft = bullet[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
			float bulletRight = bullet[cnt].pos.x + CHARACTER_COLLISION_SIZEX;
			float bulletUp = bullet[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
			float bulletDown = bullet[cnt].pos.y + CHARACTER_COLLISION_SIZEY;
			// 当たり判定
			if (enemyRight < bulletLeft)
			{// プレイヤーの右側より奥に敵がいる
				continue; // 当たらない
			}
			if (enemyLeft > bulletRight)
			{// プレイヤーの左側より奥に敵がいる
				continue;
			}
			if (enemyUp > bulletDown)
			{// プレイヤーの上側より奥に敵がいる
				continue;
			}
			if (enemyDown < bulletUp)
			{// プレイヤーの下側より奥に敵がいる
				continue;
			}
			return true;
		}
	}
	// どの弾とも当たっていない
	return false;
}
// 動く床の判定
bool PlayerCollisionMoveWall(PLAYER* player)
{
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;

	MOVEFIELD* moveFieldArray = GetMoveField();

	for (int cnt = 0; cnt < FIELD_MOVE_MAX; cnt++)
	{
		if (!moveFieldArray[cnt].bUse)
		{
			continue;
		}

		/*float fieldLeft = moveFieldArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float fieldRight = moveFieldArray[cnt].pos.x + moveFieldArray[cnt].scl.width - CHARACTER_COLLISION_SIZEX;
		float fieldUp = moveFieldArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float fieldDown = moveFieldArray[cnt].pos.y + moveFieldArray[cnt].scl.height - CHARACTER_COLLISION_SIZEY;*/

		float fieldMoveLeft = moveFieldArray[cnt].pos.x;
		float fieldMoveRight = moveFieldArray[cnt].pos.x + moveFieldArray[cnt].scl.width;
		float fieldMoveUp = moveFieldArray[cnt].pos.y;
		float fieldMoveDown = moveFieldArray[cnt].pos.y + moveFieldArray[cnt].scl.height;

		if (playerRight < fieldMoveLeft ||
			playerLeft > fieldMoveRight ||
			playerUp > fieldMoveDown ||
			playerDown < fieldMoveUp)
		{
			continue;
		}

		return true;
	}
	return false;
}

// 消える床の判定
bool PlayerCollisionDisWall(PLAYER* player)
{
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;

	FIELDDIS* disFieldArray = GetDisField();


	for (int cnt = 0; cnt < FIELD_DIS_MAX; cnt++)
	{
		if (!disFieldArray[cnt].bUse  || !disFieldArray[cnt].isActive)
		{
			return false;
		}

		/*float fieldLeft = moveFieldArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float fieldRight = moveFieldArray[cnt].pos.x + moveFieldArray[cnt].scl.width - CHARACTER_COLLISION_SIZEX;
		float fieldUp = moveFieldArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float fieldDown = moveFieldArray[cnt].pos.y + moveFieldArray[cnt].scl.height - CHARACTER_COLLISION_SIZEY;*/

		float fieldDisLeft = disFieldArray[cnt].pos.x;
		float fieldDisRight = disFieldArray[cnt].pos.x + disFieldArray[cnt].scl.width;
		float fieldDisUp = disFieldArray[cnt].pos.y;
		float fieldDisDown = disFieldArray[cnt].pos.y + disFieldArray[cnt].scl.height;

		if (playerRight < fieldDisLeft ||
			playerLeft > fieldDisRight ||
			playerUp > fieldDisDown ||
			playerDown < fieldDisUp)
		{
			continue;
		}

		return true;
	}
	return false;
}

bool PlayerCollisionItem(PLAYER* player)
{
	// キャラクターの矩形を作成
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;
	// 敵キャラクターの構造体ポインターを取得
	ITEM* itemArray = GetItem();
	// すべての敵構造体配列とチェック
	for (int cnt = 0; cnt < ITEM_NUM; cnt++)
	{
		if (itemArray[cnt].use == false)
		{// 配列の敵の情報が有効でない
			continue;
		}
		// キャラクターの矩形を作成
		float itemLeft = itemArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float itemRight = itemArray[cnt].pos.x + CHARACTER_COLLISION_SIZEX;
		float itemUp = itemArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float itemDown = itemArray[cnt].pos.y + CHARACTER_COLLISION_SIZEY;
		// 当たり判定
		if (playerRight < itemLeft)
		{// プレイヤーの右側より奥に敵がいる
			continue;
		}
		if (playerLeft > itemRight)
		{// プレイヤーの左側より奥に敵がいる
			continue;
		}
		if (playerUp > itemDown)
		{// プレイヤーの上側より奥に敵がいる
			continue;
		}
		if (playerDown < itemUp)
		{// プレイヤーの下側より奥に敵がいる
			continue;
		}
		// 当たり
		RemoveItem(cnt);	// 該当のアイテムを削除する
		return true;
	}

	// どの弾とも当たっていない
	return false;
}

// ゴールの当たり判定
bool GoalCollision(PLAYER* player)
{
	// キャラクターの矩形を作成
	float playerLeft = player->pos.x - CHARACTER_COLLISION_SIZEX;
	float playerRight = player->pos.x + CHARACTER_COLLISION_SIZEX;
	float playerUp = player->pos.y - CHARACTER_COLLISION_SIZEY;
	float playerDown = player->pos.y + CHARACTER_COLLISION_SIZEY;
	// ゴールオブジェクト情報取得
	GOALOBJECT* goalArray = GetGoalObjectPos();
	// すべての敵構造体配列とチェック
	for (int cnt = 0; cnt < ITEM_NUM; cnt++)
	{
		if (goalArray[cnt].use == false)
		{// 配列の敵の情報が有効でない
			continue;
		}
		// キャラクターの矩形を作成
		float goalLeft = goalArray[cnt].pos.x - CHARACTER_COLLISION_SIZEX;
		float goalRight = goalArray[cnt].pos.x + CHARACTER_COLLISION_SIZEX;
		float goalUp = goalArray[cnt].pos.y - CHARACTER_COLLISION_SIZEY;
		float goalDown = goalArray[cnt].pos.y + CHARACTER_COLLISION_SIZEY;
		// 当たり判定
		if (playerRight < goalLeft)
		{// プレイヤーの右側より奥に敵がいる
			continue;
		}
		if (playerLeft > goalRight)
		{// プレイヤーの左側より奥に敵がいる
			continue;
		}
		if (playerUp > goalDown)
		{// プレイヤーの上側より奥に敵がいる
			continue;
		}
		if (playerDown < goalUp)
		{// プレイヤーの下側より奥に敵がいる
			continue;
		}
		// 当たり
		RemoveGoal(cnt);	// 該当のアイテムを削除する
		return true;
	}

	// どのゴールとも当たっていない
	return false;
}

// ワイヤーオブジェクトの当たり判定
bool CollisionWireObject(WIREOBJECT* obj)
{
	return false;
}