#include "NEPlayer.h"
#include "NECharacter.h"
using namespace NeapuEngine;

#define DIR_LEFT  0x02
#define DIR_UP    0x03
#define DIR_RIGHT 0x08
#define DIR_DOWN  0x09
#define DIR_HORIZONTAL 0x02
#define DIR_VERTICAL   0x08

Player::Player(String strName, GameObject* pParent)
    : Character(strName, pParent)
    , m_nKeyLeft(0x25)
    , m_nKeyUp(0x26)
    , m_nKeyRight(0x27)
    , m_nKeyDown(0x28)
{
    
}

void Player::fixedTick() 
{
    /*要实现这么一个效果
	* 按住左反向键的同时按右方向键
	* 此时人物应该像右移动
	* 如果在左方向键没有松开之前松开了又方向键
	* 人物就应该像左移动
	* 反过来同理
	* 总而言之就是同一个轴上的两个方向键
	* 如果同时按下了
	* 后按的那一个会覆盖前一个
	* 如果后按的先松开
	* 则恢复前一个的方向
	*/

    static char dir[4] = {0};//left 1 up 2 right 3 down 4
    if(isKeyDown(m_nKeyLeft)){
        for(int i=0;i<4;i++){
            if(dir[i]==DIR_LEFT || dir[i]==0){
                dir[i]=DIR_LEFT;
                break;
            }
        }
    }else{
        for(int i=0;i<4&&dir[i]!=0;i++){
            if(dir[i]==DIR_LEFT){
                for(int j=i;j<3;j++){
                    dir[j]=dir[j+1];
                }
                dir[3]=0;
                break;
            }
        }
    }

    if(isKeyDown(m_nKeyUp)){
        for(int i=0;i<4;i++){
            if(dir[i]==DIR_UP || dir[i]==0){
                dir[i]=DIR_UP;
                break;
            }
        }
    }else{
        for(int i=0;i<4&&dir[i]!=0;i++){
            if(dir[i]==DIR_UP){
                for(int j=i;j<3;j++){
                    dir[j]=dir[j+1];
                }
                dir[3]=0;
                break;
            }
        }
    }

    if(isKeyDown(m_nKeyRight)){
        for(int i=0;i<4;i++){
            if(dir[i]==DIR_RIGHT || dir[i]==0){
                dir[i]=DIR_RIGHT;
                break;
            }
        }
    }else{
        for(int i=0;i<4&&dir[i]!=0;i++){
            if(dir[i]==DIR_RIGHT){
                for(int j=i;j<3;j++){
                    dir[j]=dir[j+1];
                }
                dir[3]=0;
                break;
            }
        }
    }

    if(isKeyDown(m_nKeyDown)){
        for(int i=0;i<4;i++){
            if(dir[i]==DIR_DOWN || dir[i]==0){
                dir[i]=DIR_DOWN;
                break;
            }
        }
    }else{
        for(int i=0;i<4&&dir[i]!=0;i++){
            if(dir[i]==DIR_DOWN){
                for(int j=i;j<3;j++){
                    dir[j]=dir[j+1];
                }
                dir[3]=0;
                break;
            }
        }
    }

    if(dir[0]!=0){
        if(m_MoveMode==MoveMode::Free){
            Vector2 v;
            for(int i=3;i>=0;i--){
                if(dir[i]&DIR_HORIZONTAL && v.x==0.f && dir[i]==DIR_LEFT){
                    v.x=-m_fHorizontalSpeed;
                }else if(dir[i]&DIR_HORIZONTAL && v.x==0.f && dir[i]==DIR_RIGHT){
                    v.x=m_fHorizontalSpeed;
                }else if(dir[i]&DIR_VERTICAL && v.y==0.f && dir[i]==DIR_UP){
                    v.y=-m_fVerticalSpeed;
                }else if(dir[i]&DIR_VERTICAL && v.y==0.f && dir[i]==DIR_DOWN){
                    v.y=m_fVerticalSpeed;
                }
            }
            setVelocity(v);
        }else{
            Vector2 v;
            for(int i=3;i>=0;i--){
                if(dir[i]!=0){
                    switch (dir[i]) {
                        case DIR_LEFT:v.x=-m_fHorizontalSpeed;break;
                        case DIR_RIGHT:v.x=m_fHorizontalSpeed;break;
                        case DIR_UP:v.y=m_fVerticalSpeed;break;
                        case DIR_DOWN:v.y=m_fVerticalSpeed;break;
                    }
                    break;
                }
            }
            setVelocity(v);
        }
    }
}
