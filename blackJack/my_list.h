#pragma once

struct card{
  int val;
  int pic;
};
typedef struct card card_t;


struct node {
  card_t card;
  struct node *next;
};
typedef struct node node_t;
typedef node_t *list; 


//lstをリストとみて全て表示する
void  show_list(list lst);


//lstをカードとみて全て表示する
void  show_card(list lst);


//lstのカード情報を表示する
// !! (lstのみ、次のリスト以降は表示しない) !!
void  show_card_info(list lst);


//lstのカード情報を取得する
// !! (lstのみ、次のリスト以降は返却しない) !!
card_t  get_card(list lst);


//カード情報vをlstに追加したリストを返す
list  cons(card_t v, list lst);


//空リストかどうか返す
int   isEmpty(list lst);


//リストの個数を1から数えて返す
//空リストの場合は0
int   get_list_size(list lst);
int   __get_list_size(list lst, int n);


//空リストを返す
list  emptyList(void);


//リストを配列とみて、lstのn番目のリストを返す
list  get_list(list lst, int n);
list  __get_list(list lst, int n, int k);


//リストを配列とみて、lstのn番目のリストに
//カード情報vを設定する
void  set_card(list lst, card_t v,int n);
void  __set_card(list lst, card_t v, int n, int k);


//デバッグ用。
void debug_message(char str[]);


//52枚のカードを生成する。
list init_card(void);


//lstをシャッフルする。
void shuffle_list(list lst);


//先頭リストを除いたリストを返す
list exceptHeadList(list lst);


//リストを全部消す
list deleteList(list lst);


//stackから1枚カードを取り出し、
//lstの先頭に加えたリストを返す。
list transferList(list lst);
