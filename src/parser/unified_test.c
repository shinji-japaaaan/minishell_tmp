#include "../../include/minishell.h"
#include "parser.h"

int main(void)
{
    // テストケース 1: 簡単な環境変数展開
    char *str1 = strdup("Hello $USER, welcome to the $SHELL!");
    char *converted_str1 = expansion(str1);
    printf("Test 1 - Expanded: %s\n", converted_str1);
    free(converted_str1);

    // テストケース 2: クォートを含む文字列
    char *str2 = strdup("This is a 'test string' with single quotes.");
    char *converted_str2 = expansion(str2);
    printf("Test 2 - Expanded: %s\n", converted_str2);
    free(converted_str2);

    // テストケース 3: 複数の環境変数
    char *str3 = strdup("The home directory is $HOME and the user is $USER.");
    char *converted_str3 = expansion(str3);
    printf("Test 3 - Expanded: %s\n", converted_str3);
    free(converted_str3);

    // テストケース 4: 履歴リストへの追加と表示
    History *history = init_history(5);
    add_to_history(history, "echo $USER");
    add_to_history(history, "ls -l");
    add_to_history(history, "pwd");
    printf("Test 4 - History:\n");
    for (int i = 0; i < history->count; i++) {
        printf("%s\n", history->entries[i]);
    }

    // テストケース 5: パーサーとトークン化の動作
    char *input = "echo $USER | grep \"pattern\" > output.txt";
    t_linked_list *parsed_list = parser(input);
    printf("Test 5 - Parsed List:\n");
    linked_list_print(parsed_list);

    // メモリ解放
    linked_list_free(parsed_list);
    free_history(history);

    return 0;
}
