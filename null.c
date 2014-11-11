//github用テストファイル

/*
 学生番号：３４５０３５
 名前　　：西野佑基
 */
#include <stdio.h>
#include <eggx.h>
#include <stdlib.h>
#include <time.h>
#define ENEMY 5    //敵の数を管理
#define ZANKI 3    //残機数を管理

//プロトタイプ宣言
int title(void);
int eventenemy(int x,int color,int y,int r);
int eventpack(int x,int y);
int eventpack_yowaenemy(int x,int y,int r);
int game(void);
int controls(void);
int packman(void);
int packmandot(void);
int packmandeath(void);
int doteat(void);
int enemyrand(void);
int enemydot(void);
int yowa_enemyrand(void);
int yowa_enemydot(void);
int yowa_enemydeath(void);
int wallmake(void);
int powerfood(void);
int ending(void);

//システムに関する変数の宣言。キーボード入力の管理と保存、乱数の管理、壁判定の管理(x,y)、window
//パワー餌判定(0通常)、現在のステージ数
int keyboard,keyhozon=-1,ransuu=-1,win,clear=0;
int power_food=0,power_time=0,power_first=0,stagenow;
//敵に関する変数の宣言。敵番号の管理,座標の管理、１マスの移動描画の管理、向きの管理、目玉の管理,死亡時間の管理,スタートの方向指定(直線移動敵用)
int roop,high[ENEMY],length[ENEMY],ugoki[ENEMY],muki[ENEMY],count[ENEMY],death[ENEMY],starter[ENEMY];
//主人公に影響する変数の宣言。スコアと残機の管理、座標の管理、向きの管理、１マスの移動描画の管理
int score,zanki,x,y,packmuki,packugoki,packmouth;
//マップの生成
int kabe[21][21];

int stage1[21][21]={    //ステージ1　kabe[21−y軸][x軸]で管理
    //kabe=0は壁、1は空き地、2は未通過、3はパワー餌
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,0},
    {0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
    {0,1,3,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,3,1,0},
    {0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,1,1,1,2,1,1,1,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,1,0},
    {0,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0},
    {0,1,0,1,0,1,1,1,1,1,3,1,1,1,1,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,2,2,2,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,2,2,2,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,2,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0},
    {0,1,3,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,3,1,0},
    {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

//ステージ2
int stage2[21][21]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,0,0},
    {0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,0,0},
    {0,0,0,1,0,1,0,1,1,1,3,1,1,1,0,1,0,1,0,0,0},
    {0,1,1,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,1,1,0},
    {0,1,0,1,0,1,0,1,0,2,2,2,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,3,0,1,0,2,2,2,0,1,0,3,0,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,0,2,0,0,1,0,0,0,1,0,1,0},
    {0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

//ステージ3
int stage3[21][21]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0},
    {0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0},
    {0,1,0,1,1,1,0,1,0,0,1,0,0,1,0,1,1,1,0,1,0},
    {0,1,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0},
    {0,1,0,1,1,1,0,1,0,0,2,0,0,1,0,1,1,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,0,3,0,0,1,0,0,0,1,0,1,0},
    {0,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0},
    {0,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,0,1,0},
    {0,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1,0},
    {0,1,0,1,0,0,0,1,0,2,2,2,0,1,0,0,0,1,0,1,0},
    {0,1,0,1,1,1,0,1,0,2,2,2,0,1,0,1,1,1,0,1,0},
    {0,1,0,0,0,1,0,1,0,0,2,0,0,1,0,1,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0},
    {0,1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

//デバッグ用
int stage_debug[21][21]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},};



int main(void) {
    int sentaku=1,rooper=0,timer,color;
    //呼び出しと画面の初期設定
    win=gopen(630,630);
    winname(win, "LastExam_Packman");
    gsetnonblock(ENABLE);                       //ノンブロッキングモードに移行
    srand((unsigned int)time(NULL));            //乱数取り開始
    //タイトル画面の処理
    while(1){                                   //EXITが押されるまでのループ管理
        keyboard=ggetch();
        if(keyboard==30)if(sentaku>1)sentaku--; //選択肢を上げる
        if(keyboard==31)if(sentaku<3)sentaku++; //選択肢を下げる
        if(keyboard==13){                       //エンター入力で処理開始
            if(sentaku==1)game();               //ゲーム処理部分に移行
            else if(sentaku==2)controls();      //動作説明表示に移行
            else if(sentaku==3)break;           //ゲーム終了
            rooper=0;
        }
        if(stagenow>1)break;                    //プレイ履歴があり、ここに戻ってくればゲーム終了
        newpen(win,1);
        if(sentaku==1)drawrect(win,255,245,125,30);   //四角い枠を書く
        if(sentaku==2)drawrect(win,255,195,125,30);   //四角い枠を書く
        if(sentaku==3)drawrect(win,255,145,125,30);   //四角い枠を書く
        title();                                      //タイトル画面を表示し続ける
        msleep(20);                                   //0.1秒待機
        gclr(win);
        rooper++;                                     //タイトル画面の起動秒数計測
        //待機時間中6秒毎にイベント実行。確率分岐で発生
        if(rooper%300==0){ransuu=rand();color=rand();}//一定時間毎にランダム生成
        timer=(rooper%300)*2;                         //イベントキャラ移動用変数の管理
        //イベントの実行部分(８パターン)
        if(ransuu%8==0)eventenemy(timer,color%4+2,85,2);
        if(ransuu%8==1)eventenemy(400-timer,color%4+2,85,2);
        if(ransuu%8==2)eventpack(timer,220);
        if(ransuu%8==3)eventpack_yowaenemy(timer,220,2);
        if(ransuu%8==4){eventenemy(timer,2,85,2);eventenemy(timer-50,3,85,2);eventenemy(timer-100,4,85,2);}
        if(ransuu%8==5){eventenemy(400-timer+100,2,85,2);eventenemy(400-timer+50,3,85,2);eventenemy(400-timer,4,85,2);}
        if(ransuu%8==6){eventpack(timer,220);eventenemy(timer,color%4+2,85,2);}
        if(ransuu%8==7){eventpack(timer-150,220);eventpack(timer-100,220);eventpack(timer-50,220);}
    }
    return 0;
}


//タイトル画面表示
int title(void){
    //[PACKMAN]のロゴ
    newpen(win,7);
    fillrect(win,30,400,15,150);    //P
    fillrect(win,30,475,75,15);
    fillrect(win,30,550,75,15);
    fillrect(win,105,490,15,60);
    
    fillrect(win,135,400,50,15);    //A
    fillrect(win,120,415,15,35);
    fillrect(win,185,415,15,60);
    fillrect(win,135,450,50,15);
    fillrect(win,135,475,50,15);
    
    fillrect(win,215,415,15,45);    //C
    fillrect(win,230,400,45,15);
    fillrect(win,230,460,45,15);
    
    fillrect(win,285,400,15,75);    //K
    fillrect(win,300,425,15,15);
    fillrect(win,315,440,15,15);
    fillrect(win,315,400,15,25);
    
    fillrect(win,340,400,15,50);    //M
    fillrect(win,370,400,15,45);
    fillrect(win,400,400,15,45);
    fillrect(win,355,435,15,15);
    fillrect(win,385,435,15,15);
    
    fillrect(win,425,405,15,25);    //A
    fillrect(win,440,400,35,10);
    fillrect(win,475,405,15,40);
    fillrect(win,440,425,35,10);
    fillrect(win,440,445,35,10);
    
    fillrect(win,500,400,15,50);    //N
    fillrect(win,535,400,15,45);
    fillrect(win,500,430,35,15);
    
    //packman
    fillarc(win,500,500,30,30,30,330,1);
    //タイトル画面選択肢文字表示
    newpen(win,1);
    drawstr(win,290,250,24,0.0,"START");
    drawstr(win,270,200,24,0.0,"CONTROLS");
    drawstr(win,295,150,24,0.0,"EXIT");
    return 0;
}


int eventenemy(int x,int color,int tate2,int r){//x=x軸、color＝敵の色、tate2=y軸,r＝倍率
    int yoko2;    //動作調整変数
    int cllen,cihi; //倍率
    cllen=r;
    cihi=r;
    yoko2=x-125;
    //体の描画
    newpen(win,color);
    fillrect(win,(30*cllen+yoko2)*2,(30*cihi+tate2)*2,4,36);
    fillrect(win,(30*cllen+2+yoko2)*2,(30*cihi+2+tate2)*2,4,44);
    fillrect(win,(30*cllen+4+yoko2)*2,(30*cihi+4+tate2)*2,4,44);
    fillrect(win,(30*cllen+6+yoko2)*2,(30*cihi+2+tate2)*2,4,52);
    fillrect(win,(30*cllen+8+yoko2)*2,(30*cihi+tate2)*2,4,56);   //5ドット目
    fillrect(win,(30*cllen+10+yoko2)*2,(30*cihi+tate2)*2,4,60);
    fillrect(win,(30*cllen+12+yoko2)*2,(30*cihi+4+tate2)*2,4,52);
    fillrect(win,(30*cllen+14+yoko2)*2,(30*cihi+4+tate2)*2,4,52);
    fillrect(win,(30*cllen+16+yoko2)*2,(30*cihi+tate2)*2,4,60);
    fillrect(win,(30*cllen+18+yoko2)*2,(30*cihi+tate2)*2,4,56);
    fillrect(win,(30*cllen+20+yoko2)*2,(30*cihi+2+tate2)*2,4,52);
    fillrect(win,(30*cllen+22+yoko2)*2,(30*cihi+4+tate2)*2,4,44);
    fillrect(win,(30*cllen+24+yoko2)*2,(30*cihi+2+tate2)*2,4,44);
    fillrect(win,(30*cllen+26+yoko2)*2,(30*cihi+tate2)*2,4,36);
    //左目の描画
    newpen(win,1);
    fillrect(win,(30*cllen+6+yoko2)*2,(30*cihi+12+tate2)*2,4,12);
    fillrect(win,(30*cllen+8+yoko2)*2,(30*cihi+10+tate2)*2,8,20);
    fillrect(win,(30*cllen+12+yoko2)*2,(30*cihi+12+tate2)*2,4,12);
    //右目の描画
    fillrect(win,(30*cllen+18+yoko2)*2,(30*cihi+12+tate2)*2,4,12);
    fillrect(win,(30*cllen+20+yoko2)*2,(30*cihi+10+tate2)*2,8,20);
    fillrect(win,(30*cllen+24+yoko2)*2,(30*cihi+12+tate2)*2,4,12);
    //目玉の描画
    if(ransuu%8==1||ransuu%8==5){//タイトル画面・横移動敵の場合に目を左向きにする
        yoko2-=4;
        tate2-=1;
    }
    newpen(win,0);
    fillrect(win,(30*cllen+10+yoko2)*2,(30*cihi+12+tate2)*2,8,8);
    fillrect(win,(30*cllen+22+yoko2)*2,(30*cihi+12+tate2)*2,8,8);
    return 0;
}


int eventpack(int x,int y){//
    //パックマン本体
    newpen(win,7);
    fillcirc(win,x*2,y+100,30,30);
    //パックマン口
    newpen(win,0);
    fillarc(win,x*2,y+100,30,30,0,x%30,1);
    fillarc(win,x*2,y+100,30,30,360-x%30,360,1);
    return 0;
}


int eventpack_yowaenemy(int xx,int y,int r){
    int x;              //逆方向移動用
    int cllen,cihi; //倍率
    int tate2,yoko2;    //調整用
    if(stagenow<1)tate2=85;//タイトル画面専用調整
    else tate2=75;     //エンディング画面用調整
    x=400-xx;           //逆方向から移動
    yoko2=x-125;
    cllen=r;    //倍率調整
    cihi=r;     //倍率調整
    //パックマン表示
    newpen(win,7);
    fillcirc(win,x*2,y+100,30,30);
    newpen(win,0);
    fillarc(win,x*2,y+100,30,30,180-x%30,180+x%30,1);
    //よわい敵表示
    newpen(win, 4);
    fillrect(win,(30*cllen+yoko2)*2,(30*cihi+tate2)*2,4,36);
    fillrect(win,(30*cllen+2+yoko2)*2,(30*cihi+2+tate2)*2,4,44);
    fillrect(win,(30*cllen+4+yoko2)*2,(30*cihi+4+tate2)*2,4,44);
    fillrect(win,(30*cllen+6+yoko2)*2,(30*cihi+2+tate2)*2,4,52);
    fillrect(win,(30*cllen+8+yoko2)*2,(30*cihi+tate2)*2,4,56);   //5ドット目
    fillrect(win,(30*cllen+10+yoko2)*2,(30*cihi+tate2)*2,4,60);
    fillrect(win,(30*cllen+12+yoko2)*2,(30*cihi+4+tate2)*2,4,52);
    fillrect(win,(30*cllen+14+yoko2)*2,(30*cihi+4+tate2)*2,4,52);
    fillrect(win,(30*cllen+16+yoko2)*2,(30*cihi+tate2)*2,4,60);
    fillrect(win,(30*cllen+18+yoko2)*2,(30*cihi+tate2)*2,4,56);
    fillrect(win,(30*cllen+20+yoko2)*2,(30*cihi+2+tate2)*2,4,52);
    fillrect(win,(30*cllen+22+yoko2)*2,(30*cihi+4+tate2)*2,4,44);
    fillrect(win,(30*cllen+24+yoko2)*2,(30*cihi+2+tate2)*2,4,44);
    fillrect(win,(30*cllen+26+yoko2)*2,(30*cihi+tate2)*2,4,36);
    //目
    newpen(win,9);
    fillrect(win,(30*cllen+8+yoko2)*2,(30*cihi+14+tate2)*2,8,8);
    fillrect(win,(30*cllen+16+yoko2)*2,(30*cihi+14+tate2)*2,8,8);
    //口
    fillrect(win,(30*cllen+2+yoko2)*2,(30*cihi+6+tate2)*2,4,4);
    fillrect(win,(30*cllen+8+yoko2)*2,(30*cihi+6+tate2)*2,8,4);
    fillrect(win,(30*cllen+16+yoko2)*2,(30*cihi+6+tate2)*2,8,4);
    fillrect(win,(30*cllen+24+yoko2)*2,(30*cihi+6+tate2)*2,4,4);
    fillrect(win,(30*cllen+4+yoko2)*2,(30*cihi+8+tate2)*2,8,4);
    fillrect(win,(30*cllen+12+yoko2)*2,(30*cihi+8+tate2)*2,8,4);
    fillrect(win,(30*cllen+20+yoko2)*2,(30*cihi+8+tate2)*2,8,4);
    return 0;
}


//ゲーム処理部分
int game(void){
    int tate,yoko,zankiroop,gameover=0;
    stagenow=1;
    gclr(win);
    zanki=ZANKI;//残機数の管理
    while(1){
        //ステージ毎のフィールド設定読み込み
        for(tate=0;tate<21;tate++){
            for(yoko=0;yoko<21;yoko++){
                if(stagenow==1)kabe[tate][yoko]=stage1[tate][yoko];
                if(stagenow==2)kabe[tate][yoko]=stage2[tate][yoko];
                if(stagenow==3)kabe[tate][yoko]=stage3[tate][yoko];
            }
        }
        //初期設定(敵・プレイヤーの初期位置決定)
        wallmake();
        for(roop=0;roop<ENEMY;roop++){
            high[roop]=14;
            length[roop]=10;
            ugoki[roop]=0;
            muki[roop]=30;
            count[roop]=0;
            starter[roop]=1;//直線移動敵を強制で上、次に右か左に移動させる
        }
        x=10;y=7;packmuki=-1;   //初期設定
        gsetnonblock(DISABLE);  //ノンブロッキングモードを解除
        newpen(win,1);
        drawstr(win,240,350,24,0.0,"PLESS_ANY_KEY");
        ggetch();
        gsetnonblock(ENABLE); //ノンブロッキングモードを開始
        //ゲーム開始
        while(1){
            if(clear>=1)break;//勝利時、暫定ゲームクリア画面に
            keyhozon=ggetch();
            if(keyhozon>=28&&keyhozon<=31)keyboard=keyhozon;//入力されていて、前と一致していないとき
            packman();      //パックマンの処理
            powerfood();    //パワー餌残り時間の処理
            for(roop=0;roop<ENEMY;roop++){//敵動きの処理部分
                doteat();       //敵の動きを操作する
                if((power_food!=0&&x==length[roop]&&y==high[roop])||death[roop]==1){death[roop]=1;yowa_enemydeath();}//敵死亡
                if(death[roop]==0&&x==length[roop]&&y==high[roop]&&zanki==1){clear=2;break;}//ゲームオーバー
                if(death[roop]==0&&x==length[roop]&&y==high[roop]&&zanki>1){zanki--;packmandeath();}//パックマン死亡
            }
            newpen(win,1);
            drawstr(win,400,600,24,0,"SCORE:%d",score);//スコア表示
            newpen(win,7);
            for(zankiroop=0;zankiroop<zanki;zankiroop++){//残機数表示
                fillarc(win,200+zankiroop*40,615,10,10,0,150,1);
                fillarc(win,200+zankiroop*40,615,10,10,210,360,1);
            }
            msleep(50);
            gclr(win);
            wallmake();
        }
        
        //クリア画面表示
        while(1){
            keyboard=ggetch();
            newpen(win,1);
            drawstr(win,200,280,24,0,"Please pless \"Q\" key");
            
            if(clear==1){//ゲームクリア時のイベント
                drawstr(win,260,340,24,0,"Game Clear");
            }
            else{//ゲームオーバー時のイベント
                drawstr(win,260,340,24,0,"Game Over");
                gameover=1;
                for(roop=0;roop<ENEMY;roop++)doteat();
            }
            if(keyboard==113){//Qキー入力で終了
                break;
            }
            msleep(50);
            gclr(win);
            wallmake();
        }
        //ゲームクリア後、ステージ変更
        stagenow++;
        clear=0;                   //暫定クリアの初期化
        power_food=0;power_first=0;//パワー餌判定の初期化
        gclr(win);
        if(gameover==1){stagenow=0;break;}//ゲームオーバー・3ステージ目クリアでゲーム終了処理
        else if(stagenow>3)break;
    }
    if(stagenow>3&&gameover==0)ending();//ゲームクリアで実行終了
    return 0;
}


//操作説明表示部分
int controls(void){
    int ender,rooper=0,rooper2=0,color=2;
    gclr(win);
    while(1){
        ender=ggetch();
        //パックマンの解説
        ransuu=2;//敵の目を右向きにする
        eventenemy(80,4,200,2);
        eventpack(80,450);
        newpen(win,7);
        fillcirc(win,200,550,8,8);
        fillcirc(win,240,550,8,8);
        newpen(win,1);
        drawstr(win,250,570,24,0.0,"Pac-Man escapes from an enemy. ");
        drawstr(win,280,540,24,0.0,"All food must be eaten. ");
        //キー入力の解説
        newpen(win,1);
        drawrect(win,100,450,40,30);
        drawstr(win,113,457,FONTSET,0.0,"↑");
        drawrect(win,100,420,40,30);
        drawstr(win,113,427,FONTSET,0.0,"↓");
        drawrect(win,60,420,40,30);
        drawstr(win,153,427,FONTSET,0.0,"→");
        drawrect(win,140,420,40,30);
        drawstr(win,73,427,FONTSET,0.0,"←");
        drawstr(win,250,460,24,0.0,"Please press the arrow key");
        drawstr(win,480,430,24,0.0,"at movement. ");
        //パワー餌の処理説明&ムービー
        drawstr(win,250,380,24,0.0,"Power food strengthens Pac-Man. ");
        if(rooper%800==0)rooper=0;
        rooper+=4;
        if(rooper<200){eventenemy(rooper,3,85,2);eventpack(rooper,220);}//パックマン逃げる
        else if(rooper<300){eventenemy(200,3,85,2);eventpack(200,220);newpen(win,1);drawstr(win,430,340,24,0.0,"!");}//パックマン餌見つける
        else if(rooper<400){eventpack_yowaenemy(200,220,2);newpen(win,1);drawstr(win,330,340,24,0.0,"!!");}
        else {eventpack_yowaenemy(rooper-200,220,2);}
        newrgbcolor(win,255.0,129.0,25.0);          //パワー餌の色設定
        if(rooper<300)fillcirc(win,430,320,10,10);  //パワー餌の表示
        //最後の説明
        newpen(win,2);
        drawstr(win,10,200,24,0.0,"It is a game clearance when all the food is taken!");
        drawstr(win,190,170,24,0.0,"Please enjoy a Packman! ");
        //空白ムービー
        rooper2+=4;
        if(rooper2%500==0)color++;//1回実行毎に色を変える
        if(color==7)color=2;      //5体出現で赤色に戻す
        ransuu=1;//敵の目を左向きにする
        eventpack(rooper2%500-100,30);
        eventenemy(500-rooper2%500,color,20,1);
        newpen(win,1);
        drawstr(win,470,0,18,0.0,"Pless Shift Key...");
        msleep(50);
        gclr(win);
        if(ender==32)break;
    }
    return 0;
}


//パックマンの動作処理
int packman(void){
    packmandot();
    if((keyboard==30||keyboard==31||keyboard==28||keyboard==29)||packugoki!=0){
        if(packugoki==0){
            if(keyboard==30)if(kabe[y+1][x]!=0){packmouth=30;packugoki+=2;}
            if(keyboard==31)if(kabe[y-1][x]!=0){packmouth=31;packugoki+=2;}
            if(keyboard==28)if(kabe[y][x+1]!=0){packmouth=28;packugoki+=2;}
            if(keyboard==29)if(kabe[y][x-1]!=0){packmouth=29;packugoki+=2;}
        }
        else packugoki+=2;
        if(packugoki>=10){
            if(packmouth==30)y++;//上
            if(packmouth==31)y--;//下
            if(packmouth==28)x++;//右
            if(packmouth==29)x--;//左
            if(kabe[y][x]==1){
                kabe[y][x]=2;
                score+=100;
            }
            if(kabe[y][x]==3){
                kabe[y][x]=2;
                score+=200;
                power_food=1;
            }
            packugoki=0;
            packmouth=0;
        }
    }
    return 0;
}


//パックマン描写
int packmandot(void){
    int moutht,mouthy;
    if(packmouth==30){moutht=3;mouthy=0;}//moutht=タテ、mouthy=ヨコ　口の方向管理
    if(packmouth==31){moutht=-3;mouthy=0;}
    if(packmouth==28){moutht=0;mouthy=3;}
    if(packmouth==29){moutht=0;mouthy=-3;}
    newpen(win,7);
    //パックマンの向きによって口の向きを変化させる
    if(packmouth==30){
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,0,60,1);
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,120,360,1);
    }
    else if(packmouth==31){
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,300,360,1);
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,0,240,1);
    }
    else if(packmouth==28){
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,30,330,1);
    }
    else if(packmouth==29){
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,0,150,1);
        fillarc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15,210,360,1);
    }
    //向きが入力されていない場合、体のみになる
    else fillcirc(win,30*x+15+packugoki*mouthy,30*y+15+packugoki*moutht,15,15);
    return 0;
}


//パックマン死亡処理・描画
int packmandeath(void){
    int deathroop;
    //死亡時にゆっくり消えてゆくムービーの表示
    for(deathroop=0;deathroop<180;deathroop+=10){
        newpen(win,7);
        fillcirc(win,30*x+15,30*y+15,15,15);
        newpen(win,0);
        fillarc(win,30*x+15,30*y+15,15,15,180-deathroop,180+deathroop,1);
        msleep(100);
        gclr(win);
        wallmake();
    }
    msleep(1000);
    keyboard=0;//移動方向の初期化
    //敵の初期化
    for(roop=0;roop<ENEMY;roop++){
        high[roop]=14;
        length[roop]=10;
        ugoki[roop]=0;
        muki[roop]=30;
        count[roop]=0;
    }
    x=10;y=7;packmuki=-1;
    srand((unsigned int)time(NULL));
    return 0;
}


//敵の動き
int doteat(void){
    if(ugoki[roop]==0){//一マス移動した時のみ移動方向決定処理
        if(death[roop]!=0)muki[roop]=-1;    //死亡中の向き
        else if(power_food==0)enemyrand();  //通常時の移動方向取得
        else yowa_enemyrand();              //パックマンパワー餌取得時の移動方向取得
        if(muki[roop]==30)if(kabe[high[roop]+1][length[roop]]==0){enemydot();return 0;}//移動方向が壁の場合、描画のみを行って関数終了
        if(muki[roop]==31)if(kabe[high[roop]-1][length[roop]]==0){enemydot();return 0;}//処理部分で再度ループして方向を判定し直す
        if(muki[roop]==28)if(kabe[high[roop]][length[roop]+1]==0){enemydot();return 0;}
        if(muki[roop]==29)if(kabe[high[roop]][length[roop]-1]==0){enemydot();return 0;}
    }
    ugoki[roop]++;
    //通常時とパワーアップ時の敵点滅の管理・描画
    if(power_food==0||(power_time<=40&&power_time%5>=3)||(power_time>40&&power_time<=80&&power_time%12>=6)||(power_time>80&&power_time<=150&&power_time%15>=7))enemydot();
    else yowa_enemydot();
    if(ugoki[roop]==10){//壁の判定と座標移動・向きの管理と分岐
        if(muki[roop]==30)high[roop]++;
        if(muki[roop]==31)high[roop]--;
        if(muki[roop]==28)length[roop]++;
        if(muki[roop]==29)length[roop]--;
        ugoki[roop]=0;
    }
    return 0;
}


//敵の移動方向処理
int enemyrand(void){
    if(roop>=0&&roop<=1){//追いかけ型
        ransuu=rand();
        if(ransuu%4!=0){
            ransuu=rand();//乱数%2==0を弾いているので取り直し
            //主人公の座標を確認し、近づく方向にxかy軸を移動する
            if(y>high[roop]){
                if(x>length[roop]){
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=28;
                }
                else{
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=29;
                }
            }
            else{
                if(x>length[roop]){
                    if(ransuu%2==0)muki[roop]=31;
                    else muki[roop]=28;
                }
                else{
                    if(ransuu%2==0)muki[roop]=31;
                    else muki[roop]=29;
                }
            }
        }
        else{//一定確率(1/4)で完全なランダム移動
            ransuu=rand();
            if(ransuu%4==0)muki[roop]=30;
            if(ransuu%4==1)muki[roop]=31;
            if(ransuu%4==2)muki[roop]=28;
            if(ransuu%4==3)muki[roop]=29;
        }
    }
    else if(roop>=2&&roop<=3){//直線移動型
        ransuu=rand();
        if(starter[roop]==1){
            muki[roop]=30;
            starter[roop]++;
        }
        else if(starter[roop]==2){
            if(ransuu%2==0)muki[roop]=28;
            else muki[roop]=29;
            starter[roop]=0;
        }
        else{//初期の方向決定以外の判定
            if(muki[roop]==30){//上向きで壁があるとき、他三方向に移動
                if(kabe[high[roop]+1][length[roop]]==0){
                    if(ransuu%3==0)muki[roop]=28;
                    else if(ransuu%3==1)muki[roop]=29;
                    else muki[roop]=31;
                }
            }
            if(muki[roop]==31){//下向きで壁があるとき、他三方向に移動
                if(kabe[high[roop]-1][length[roop]]==0){
                    if(ransuu%3==0)muki[roop]=28;
                    else if(ransuu%3==1)muki[roop]=29;
                    else muki[roop]=30;
                }
            }
            if(muki[roop]==28){//右向きで壁があるとき、他三方向に移動
                if(kabe[high[roop]][length[roop]+1]==0){
                    if(ransuu%3==0)muki[roop]=30;
                    else if(ransuu%3==1)muki[roop]=31;
                    else muki[roop]=29;
                }
            }
            if(muki[roop]==29){//左向きで壁があるとき、他三方向に移動
                if(kabe[high[roop]][length[roop]-1]==0){
                    if(ransuu%3==0)muki[roop]=30;
                    else if(ransuu%3==1)muki[roop]=31;
                    else muki[roop]=28;
                }
            }
            //向き判定終了
        }
    }
    else if(roop>=4&&roop<=5){//同じ動き型
        ransuu=rand();
        if(ransuu%3!=0)muki[roop]=keyboard;//一定確率(2/3)でキーボードの値を取得して移動
        else{//完全なランダム移動
            ransuu=rand();
            if(ransuu%4==0)muki[roop]=30;
            if(ransuu%4==1)muki[roop]=31;
            if(ransuu%4==2)muki[roop]=28;
            if(ransuu%4==3)muki[roop]=29;
        }
    }
    else{//完全なランダム移動。敵を6体以上に増やす場合に対応
        ransuu=rand();
        if(ransuu%4==0)muki[roop]=30;
        if(ransuu%4==1)muki[roop]=31;
        if(ransuu%4==2)muki[roop]=28;
        if(ransuu%4==3)muki[roop]=29;
    }
    return 0;
}


//敵のグラフィック表示
int enemydot(void){
    int tate2=0,yoko2=0,medamaue=0,medamamigi=0;
    //敵現在の向きが上下なら±3ドット
    if(muki[roop]==30||muki[roop]==31)tate2=ugoki[roop]*3;
    else if(muki[roop]==28||muki[roop]==29)yoko2=ugoki[roop]*3;
    if(muki[roop]==31||muki[roop]==29){tate2*=-1;yoko2*=-1;}
    
    //身体の描画
    newpen(win,roop+2);
    fillrect(win,30*length[roop]+yoko2,30*high[roop]+tate2,2,18);
    fillrect(win,30*length[roop]+2+yoko2,30*high[roop]+2+tate2,2,22);
    fillrect(win,30*length[roop]+4+yoko2,30*high[roop]+4+tate2,2,22);
    fillrect(win,30*length[roop]+6+yoko2,30*high[roop]+2+tate2,2,26);
    fillrect(win,30*length[roop]+8+yoko2,30*high[roop]+tate2,2,28);   //5ドット目
    fillrect(win,30*length[roop]+10+yoko2,30*high[roop]+tate2,2,30);
    fillrect(win,30*length[roop]+12+yoko2,30*high[roop]+4+tate2,2,26);
    fillrect(win,30*length[roop]+14+yoko2,30*high[roop]+4+tate2,2,26);
    fillrect(win,30*length[roop]+16+yoko2,30*high[roop]+tate2,2,30);
    fillrect(win,30*length[roop]+18+yoko2,30*high[roop]+tate2,2,28);
    fillrect(win,30*length[roop]+20+yoko2,30*high[roop]+2+tate2,2,26);
    fillrect(win,30*length[roop]+22+yoko2,30*high[roop]+4+tate2,2,22);
    fillrect(win,30*length[roop]+24+yoko2,30*high[roop]+2+tate2,2,22);
    fillrect(win,30*length[roop]+26+yoko2,30*high[roop]+tate2,2,18);
    //左目の描画
    newpen(win,1);
    fillrect(win,30*length[roop]+6+yoko2,30*high[roop]+12+tate2,2,6);
    fillrect(win,30*length[roop]+8+yoko2,30*high[roop]+10+tate2,4,10);
    fillrect(win,30*length[roop]+12+yoko2,30*high[roop]+12+tate2,2,6);
    //右目の描画
    fillrect(win,30*length[roop]+18+yoko2,30*high[roop]+12+tate2,2,6);
    fillrect(win,30*length[roop]+20+yoko2,30*high[roop]+10+tate2,4,10);
    fillrect(win,30*length[roop]+24+yoko2,30*high[roop]+12+tate2,2,6);
    //目玉の描画
    newpen(win,0);
    if(muki[roop]==30)medamaue+=4;
    if(muki[roop]==28)medamamigi+=4;
    fillrect(win,30*length[roop]+7+medamamigi+yoko2,30*high[roop]+10+medamaue+tate2,4,4);
    fillrect(win,30*length[roop]+19+medamamigi+yoko2,30*high[roop]+10+medamaue+tate2,4,4);
    return 0;
    return 0;
}


//弱体化後の敵描画
int yowa_enemydot(void){
    int tate2=0,yoko2=0;
    //敵現在の向きが上下なら±3ドット
    if(muki[roop]==30||muki[roop]==31)tate2=ugoki[roop]*3;
    else if(muki[roop]==28||muki[roop]==29)yoko2=ugoki[roop]*3;
    if(muki[roop]==31||muki[roop]==29){tate2*=-1;yoko2*=-1;}
    //体
    newpen(win, 4);
    fillrect(win,30*length[roop]+yoko2,30*high[roop]+tate2,2,18);
    fillrect(win,30*length[roop]+2+yoko2,30*high[roop]+2+tate2,2,22);
    fillrect(win,30*length[roop]+4+yoko2,30*high[roop]+4+tate2,2,22);
    fillrect(win,30*length[roop]+6+yoko2,30*high[roop]+2+tate2,2,26);
    fillrect(win,30*length[roop]+8+yoko2,30*high[roop]+tate2,2,28);   //5ドット目
    fillrect(win,30*length[roop]+10+yoko2,30*high[roop]+tate2,2,30);
    fillrect(win,30*length[roop]+12+yoko2,30*high[roop]+4+tate2,2,26);
    fillrect(win,30*length[roop]+14+yoko2,30*high[roop]+4+tate2,2,26);
    fillrect(win,30*length[roop]+16+yoko2,30*high[roop]+tate2,2,30);
    fillrect(win,30*length[roop]+18+yoko2,30*high[roop]+tate2,2,28);
    fillrect(win,30*length[roop]+20+yoko2,30*high[roop]+2+tate2,2,26);
    fillrect(win,30*length[roop]+22+yoko2,30*high[roop]+4+tate2,2,22);
    fillrect(win,30*length[roop]+24+yoko2,30*high[roop]+2+tate2,2,22);
    fillrect(win,30*length[roop]+26+yoko2,30*high[roop]+tate2,2,18);
    //目
    newpen(win,9);
    fillrect(win,30*length[roop]+8+yoko2,30*high[roop]+14+tate2,4,4);
    fillrect(win,30*length[roop]+16+yoko2,30*high[roop]+14+tate2,4,4);
    //口
    fillrect(win,30*length[roop]+2+yoko2,30*high[roop]+6+tate2,2,2);
    fillrect(win,30*length[roop]+8+yoko2,30*high[roop]+6+tate2,4,2);
    fillrect(win,30*length[roop]+16+yoko2,30*high[roop]+6+tate2,4,2);
    fillrect(win,30*length[roop]+24+yoko2,30*high[roop]+6+tate2,2,2);
    fillrect(win,30*length[roop]+4+yoko2,30*high[roop]+8+tate2,4,2);
    fillrect(win,30*length[roop]+12+yoko2,30*high[roop]+8+tate2,4,2);
    fillrect(win,30*length[roop]+20+yoko2,30*high[roop]+8+tate2,4,2);
    return 0;
}


//弱体化後の敵移動方向処理
int yowa_enemyrand(void){
    ransuu=rand();
    if(y>high[roop]){
        if(x>length[roop]){
            if(ransuu%2==0){
                if(kabe[high[roop]-1][length[roop]]!=0)muki[roop]=31;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=28;
                    else muki[roop]=29;
                }
            }
            else{
                if(kabe[high[roop]][length[roop]-1]!=0)muki[roop]=29;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=31;
                }
            }
        }
        else{
            if(ransuu%2==0){
                if(kabe[high[roop]-1][length[roop]]!=0)muki[roop]=31;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=28;
                    else muki[roop]=29;
                }
            }
            else{
                if(kabe[high[roop]][length[roop]+1]!=0)muki[roop]=28;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=31;
                }
            }
        }
    }
    else{
        if(x>length[roop]){
            if(ransuu%2==0){
                if(kabe[high[roop]+1][length[roop]]!=0)muki[roop]=30;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=28;
                    else muki[roop]=29;
                }
            }
            else{
                if(kabe[high[roop]][length[roop]-1]!=0)muki[roop]=29;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=31;
                }
            }
        }
        else{
            if(ransuu%2==0){
                if(kabe[high[roop]+1][length[roop]]!=0)muki[roop]=30;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=28;
                    else muki[roop]=29;
                }
            }
            else{
                if(kabe[high[roop]][length[roop]+1]!=0)muki[roop]=28;
                else{
                    ransuu=rand();
                    if(ransuu%2==0)muki[roop]=30;
                    else muki[roop]=31;
                }
            }
        }
    }
    return 0;
}


//敵の死亡処理
int yowa_enemydeath(void){
    if(high[roop]>12)high[roop]--;
    else if(high[roop]<12)high[roop]++;
    else if(length[roop]>10)length[roop]--;
    else if(length[roop]<10)length[roop]++;
    else if(count[roop]==0&&death[roop]==1){count[roop]=20*10;score+=300;}//10秒間待機
    else if(count[roop]>1&&death[roop]==1)count[roop]--;
    else  {death[roop]=0;count[roop]=0;muki[roop]=30;}
    return 0;
}


//壁の描画
int wallmake(void){
    int yroop,xroop,clearhantei=0,color=2;
    //ステージ毎に壁の色を指定
    if(stagenow==1)color=2;
    if(stagenow==2)color=8;
    if(stagenow==3)color=10;
    //配列読み込みで壁作成
    for(yroop=20;yroop>=0;yroop--){
        for(xroop=0;xroop<=20;xroop++){
            newpen(win,color);
            if(kabe[yroop][xroop]==0)fillrect(win,xroop*30,yroop*30,30,30);
            newpen(win,7);
            if(kabe[yroop][xroop]==1){fillcirc(win,xroop*30+15,yroop*30+15,5,5);clearhantei++;}
            newrgbcolor(win,255.0,129.0,25.0);
            if(kabe[yroop][xroop]==3){fillcirc(win,xroop*30+15,yroop*30+15,10,10);}
        }
    }
    if(clearhantei==0)clear=1;
    return 0;
}


//パワー餌取得の処理
int powerfood(void){
    if(power_food!=0&&power_first==0){power_time=20*10;power_first=1;}  //10秒間弱体化
    if(power_time>0)power_time--;                                       //0,05秒づつ減少
    if(power_time==0&&power_food!=0){power_food=0;power_first=0;}  //パワー餌の判定終了
    return 0;
}


//エンディングムービー
int ending(void){
    int tate2,yoko2,x=0,y=0;
    y=200;
    tate2=75;
    yoko2=x-125;
    //敵と追われるパックマン
    for(x=-100;x<420;x+=6){
        eventpack(x,y);
        eventenemy(x,2,75,2);
        msleep(50);
        gclr(win);
        
    }
    //弱体化敵と追うパックマン
    for(x=-100;x<420;x+=6){
        eventpack_yowaenemy(x,y,2);
        msleep(50);
        gclr(win);
    }
    //パックマン
    for(x=-100;x<160;x+=6){
        eventpack(x,y);
        msleep(50);
        gclr(win);
    }
    for(x=0;x<420;x+=6){
        newpen(win,7);
        fillcirc(win,315,315,30+x,30+x);
        newpen(win,0);
        fillcirc(win,315,315,30+x,x%(30+x/3));
        msleep(50);
        gclr(win);
    }
    return 0;
}