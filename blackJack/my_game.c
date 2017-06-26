#include "my_game.h"
#include "my_list.h"
#include <string.h>
#include <stdio.h>


void exec(void){
  char strbuff[128];
  int valbuff;

  switch (game_pattern){


  case SCENE_DEMO:
    if (credits <= 0){
      isFinish = TRUE;
      break;
    }
    printf("ゲームを開始しますか？ press yes or no... ");
    scanf("%s", strbuff);
    if (strcmp(strbuff, "yes") == 0){ game_init(); game_pattern = INIT_GAME; }
    else if (strcmp(strbuff,"no") == 0){ isFinish = TRUE; }
    break;


  case INIT_GAME:
    printf("掛け金を入力してください... ");
    scanf("%d", &valbuff);
    fflush(stdin);
    if (valbuff <= 0)break;
    if (credits - valbuff < 0){
      bet = credits;
      credits = 0;
    }
    else{
      bet = valbuff;
      credits -= bet;
    }
    player_card = transferList(player_card);
    player_card = transferList(player_card);
    dealer_card = transferList(dealer_card);
    dealer_card = transferList(dealer_card);
    game_pattern = PALYER_MODE;
    break;


  case PALYER_MODE:
    if (get_score(player_card, FALSE) > 21){
      game_pattern = PLAYER_LOSE;
      break;
    }
    printf("モードを選択してください(hit,stand,double)... ");
    scanf("%s", strbuff);
    if (strcmp(strbuff, "hit") == 0)game_pattern = HIT;
    if (strcmp(strbuff, "stand") == 0)game_pattern = STAND;
    if (strcmp(strbuff, "double") == 0)game_pattern = DOUBLE;
    break;


  case PLAYER_LOSE:
    game_pattern = SCENE_DEMO;
    strcpy(strInfo, "You lose... ");
    bet = 0;
    break;


  case PLAYER_WIN:
    game_pattern = SCENE_DEMO;
    sprintf(strInfo, "you win!!  %dpt for you.", bet * 2);
    credits += bet * 2;
    bet = 0;
    break;


  case DRAW:
    game_pattern = SCENE_DEMO;
    sprintf(strInfo, "Draw!  %dpt for you.", bet);
    credits += bet;
    bet = 0;
    break;


  case HIT:
    game_pattern = PALYER_MODE;
    if (get_score(player_card, FALSE) == 21){
      strcpy(strInfo, "スコアが21ptです.standしてください.");
      break;
    }
    player_card = transferList(player_card);
    strcpy(strInfo, "カードを追加しました.");
    break;


  case STAND:
    game_pattern = RESULT;
    isResult = TRUE;
    while (get_score(dealer_card,FALSE) <= 16){
      dealer_card = transferList(dealer_card);
    }
    break;


  case RESULT:
    if (get_score(dealer_card, FALSE) > 21)game_pattern = PLAYER_WIN;
    else if (get_score(dealer_card, FALSE) > get_score(player_card, FALSE))game_pattern = PLAYER_LOSE;
    else if (get_score(dealer_card, FALSE) < get_score(player_card, FALSE))game_pattern = PLAYER_WIN;
    else game_pattern = DRAW;
    break;


  case DOUBLE:
    game_pattern = PALYER_MODE;
    if (get_score(player_card, FALSE) == 21){
      strcpy(strInfo, "スコアが21ptです.standしてください.");
      break;
    }
    if (isDouble == TRUE){
      strcpy(strInfo, "doubleは1回のみ可能です.");
      break;
    }
    if (credits - bet < 0){
      strcpy(strInfo, "クレジットが足りません.");
      break;
    }
    credits -= bet;
    bet += bet;
    isDouble = TRUE;
    game_pattern = HIT;
    break;
  }
}
//------------------------------
void initialize(void){
  strcpy(strInfo, "welcome!");
  isDouble = FALSE;
  isFinish = FALSE;
  isResult = FALSE;
  game_pattern = SCENE_DEMO;
  credits = load_credit();
  shuffle_list(stack = init_card());
  player_card = emptyList();
  dealer_card = emptyList();
  //show_all_card();
}
//------------------------------
int is_finish(void){
  system("cls");
  printf("\n");
  printf(" CREDITS: %04d   BET: %04d   %s\n\n", credits, bet, strInfo);
  printf(" プレイヤーカード(%02dpt):", get_score(player_card, FALSE));
  show_card(player_card);printf("\n");

  if (isResult == TRUE){
    printf(" ディーラーカード(%02dpt):", get_score(dealer_card,FALSE));
    show_card(dealer_card); printf("\n");
  }
  else{
    printf(" ディーラーカード(%02dpt):", get_score(dealer_card, TRUE));
    printf(" "); show_card_info(dealer_card); printf("  [ ? ] ?  \n");
  }
  printf("\n");
  return isFinish;
}
//------------------------------
void finalize(void){
  stack = deleteList(stack);
  player_card = deleteList(player_card);
  dealer_card = deleteList(dealer_card);
  //show_all_card();
}
//------------------------------
void show_all_card(void){
  printf("\n----- stack  = %3d   ----------\n\n", get_list_size(stack));
  show_card(stack);
  printf("\n\n----- player = %3d   ----------\n\n", get_list_size(player_card));
  show_card(player_card);
  printf("\n\n----- dealer = %3d   ----------\n\n", get_list_size(dealer_card));
  show_card(dealer_card);
}


int load_credit(void){
  return DEF_CREDITS;
}


//    CREDITS: 0710   BET : 0000   You lose...
//
//      プレイヤーカード(23pt) : [D] A[C] 2[D] 10    <----  加算順序のバグあり！23はおかしい。この場合は13が正解。
//      ディーラーカード(10pt) : [D] J[? ] ?
//
//      ゲームを開始しますか？ press yes or no... hit


//    バグの解消方法。
//    2回手札のカードをチェックする
//    1回目は、A以外はいつも通りに加算する、Aのときは1として計算
//    2回目は、A以外は加算しない、Aの時は10として”1回目の合計値”に加算
//    2回目は、常に21を超えるかチェックして、21以上になった時点で、Aの時10として加算する処理を終了する。


int get_score(list lst, int firstCardOnly){
  int ret = 0;
  list check_lst = lst;
  card_t tmp;
  while (!isEmpty(check_lst)){
    tmp = get_card(check_lst);
    if (tmp.val == 0)ret++;
    if (10 <= tmp.val && tmp.val < 13)ret += 10;
    if (1 <= tmp.val && tmp.val < 10)ret += tmp.val + 1;
    if (firstCardOnly == TRUE)break;
    check_lst = check_lst->next;
  }
  check_lst = lst;
  while (!isEmpty(check_lst)){
    tmp = get_card(check_lst);
    if (tmp.val == 0 && ret + 10 <= 21)ret += 10;
    if (firstCardOnly == TRUE)break;
    check_lst = check_lst->next;
  }
  return ret;
}


void game_init(void){
  finalize();
  isResult = FALSE;
  isDouble = FALSE;
  isFinish = FALSE;
  game_pattern = SCENE_DEMO;
  shuffle_list(stack = init_card());
  player_card = emptyList();
  dealer_card = emptyList();
}
