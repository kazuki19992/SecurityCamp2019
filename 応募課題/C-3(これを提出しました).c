// 共通問題C
// C言語で双方向リンクリストとそれを操作する関数
// リンクリストを生成する関数, 要素を任意の場所に挿入する関数,
//   すべての要素を順に標準出力に印字する関数
// 2019/05/25 櫛田一樹

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void MakeList(int n); //リスト作成
void InsList(int insnum); //リストへの挿入
void OutPutList(); //リストを出力する
void Del(); //リストの解放

struct LIST{
    int number;
    struct LIST *prev;
    struct LIST *next;
};

struct LIST *start;

int main(){
    int n,insnum;
    char ans;
    printf("リストを作成します。\n初期の要素数を入力してください。(2以上):");
    scanf("%d",&n);
    //入力値検査
    assert(n > 2);

    //リストの作成
    MakeList(n);

    //要素の挿入
    while(1){
        printf("要素を挿入しますか? [Y/N] : ");
        scanf("%*c%c",&ans);

        if(ans=='Y'||ans=='y'){
            //要素を挿入する場合
            printf("要素を挿入する箇所を指定してください : ");

            //バッファの中に残っている改行文字をクリア
            fflush(stdin);
            scanf("%d",&insnum);

            //入力値検査
            assert(insnum > 0 && insnum <= n);
            InsList(insnum);

        }else if(ans == 'N'||ans == 'n'){
            //要素の挿入を行わない場合
            break;

        }else{
            //想定値以外のキー入力があった場合
            printf("再入力してください\n");
            continue;

        }
    }

    //リストの全要素を出力
    OutPutList();

    //解放
    Del();
    
    return 0;
}


void OutPutList(){
    struct LIST *now;
    now = start;
    int i = 0;
    printf("---リストの全要素を出力します---\n\n");
    while(1){
        printf("%d番目の要素---\n",i+1);
        printf("  現在のアドレス= %p\n",now);
        printf("  number\t= %4d\n",now -> number);
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
}


void InsList(int insnum){
    struct LIST *now, *new; //現在注目している箇所(now),新しく生成した要素(new)

    now = start;

    //挿入する要素の生成
    new = malloc(sizeof(struct LIST));
    printf("挿入する要素のnumber : ");

    //バッファの中に残っている改行文字をクリア
    fflush(stdin);
    scanf("%d",&new -> number);
    //挿入箇所まで移動
    for(int i = 0; i < insnum-2; i++){
        now = now -> next;
    }
    
    //リストの挿入
    new -> next = now -> next; //newの次をnowの次のアドレスにする
    now -> next -> prev = new; //nowの次の要素の前のアドレスをnewにする
    now -> next = new; //nowの次をnewにする
    new -> prev = now; //newの前をnowにする


    /* ここでメモリ開放していたため想定していた動作にならなかった。 */
    // free(now);
    // free(new);

}


void MakeList(int n){
    struct LIST *p;
    int i; //ループ用

    for(i = 0;i < n;i++){
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
        printf("%d番目のLISTのnumber : ",i+1);
        //バッファの中に残っている改行文字をクリア
        fflush(stdin);
        scanf("%d",&p -> number);

        //リスト最後のnextにNULLを代入
        p -> next = NULL;

    }
}

void Del(){
    struct LIST *next;
    struct LIST *delete;
    
    //次の要素のアドレス
    next = start -> next;

    //NULLまでループ
    while(next != NULL){
        //削除ポインタの保存
        delete = next;
        //削除する要素の次のポインタを取得
        next = next -> next;

        //解放
        free(delete);
    }
}