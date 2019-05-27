// 共通問題C
// C言語で双方向リンクリストとそれを操作する関数
// リンクリストを生成する関数, 要素を任意の場所に挿入する関数,
//   すべての要素を順に標準出力に印字する関数
// 2019/05/25 櫛田一樹

#include<stdio.h>
#include<stdlib.h>

struct LIST{
    int value;
    struct LIST *prev;
    struct LIST *next;
}

struct LIST start;

void Add(int value); //要素の追加
void Delete(int value); //要素の削除
void MakeList(); //リスト作成
void Insert(int value); //リストへの挿入
void Output(); //リストを出力する
void Release(); //リストの開放

int main(){
    // int insnum,cnt = 0;//,n
    // char ans;

    start.next = NULL;
    char ans = '\0';
    int value;

    printf("q:終了 a:追加 d:削除 p:表示 i:挿入 : ");
    while(ans != 'q'){
        scanf("%c",&ans);

        //改行文字のクリア
        fflush(stdin);

        switch(ans){

            case 'a':
                printf("追加する値の入力 : ");
                scanf("%d",&value);
                Add(value);
                break;
            
            case 'd':
                printf("削除する値の入力 : ");
                scanf("%d",&value);
                Delete(value);
                break;
            
            case 'p':
                Output();
                break;
            
            case 'i':
                printf("追加する値を入力 : ");
                scanf("%d",&value);
                Insert(value);
                break;
            
            default:
                printf("再入力\n");
                break;
        }

        //改行文字のクリア
        fflush(stdin);
        printf("q:終了 a:追加 d:削除 p:表示 i:挿入 : ");
    }

    //開放を行う
    Release();

    return 0;
}

//リストを作成する関数
void Add(int data){
    struct LIST *p;
    //末尾ポインタ
    struct LIST *next_list;
    //末尾のひとつ前のポインタ
    struct *prev_list;

    p = (LIST*)malloc(sizeof(struct LIST));

    p -> value = data;
    //次の要素にNULLを入れる
    p -> next = NULL;


}
void Output(){
    struct LIST *now;
    now = start;
    int i = 0;
    printf("\n---リストの全要素を出力します---\n\n");
    while(1){
        printf("%d番目の要素---\n",i+1);
        printf("  現在のアドレス= %p\n",now);
        printf("  int data\t= %4d\n",now -> data);
        printf("  前\t\t= %p\n",now -> prev);
        printf("  次\t\t= %p\n",now -> next);
        putchar('\n');
        if(now -> next == NULL){
            break;
        }
        now = now -> next;
        i++;
    }
    printf("status : 出力完了\n全体の要素数 : %d\n",i+1);

    free(now);
}


void Insert(int insnum){
    struct LIST *now, *new; //現在注目している箇所(now),新しく生成した要素(new)

    now = start;
    new = malloc(sizeof(struct LIST));

    printf("挿入する要素のdata: ");
    scanf("%*c%d",&new -> data);

    //挿入箇所まで移動
    for(int i = 0; i < insnum-2; i++){
        now = now -> next;
    }

    //ポインタの切り替え
    new -> next = now -> next; //newの次をnowの次のアドレスにする
    now -> next -> prev = new; //nowの次の要素の前のアドレスをnewにする
    now -> next = new; //nowの次をnewにする
    new -> prev = now; //newの前をnowにする

    free(now);
    free(new);
}


void MakeList(int n){
    struct LIST *p;
    int i; //ループ用

    for(i = 0;i < 3;i++){
        //先頭の構造体の生成
        if(i == 0){
            p = malloc(sizeof(struct LIST));
            start = p;

            //ひとつ前のアドレスにNULLを代入
            p -> prev = NULL;
        
        }else{
            //次の構造体を生成
            p -> next = malloc(sizeof(struct LIST));

            //現在のアドレスを次のひとつ前のアドレスに代入
            p -> next -> prev = p;

            //次に移動
            p = p -> next;
        }

        //項目の入力
        printf("%d番目のLISTのdata : ",i+1);
        if(i==0){
            scanf("%d",&p -> data);
        }else{
            scanf("%*c%d",&p -> data);
        }

        //リスト最後のnextにNULLを代入
        p -> next = NULL;

    }
}