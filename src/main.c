/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 07:59:43 by sishizaw          #+#    #+#             */
/*   Updated: 2025/01/18 19:56:28 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int handle_internal_commands(char *command, char *args, char **env) {
    if (strcmp(command, "cd") == 0) {
        return (change_directory(args), 1);
    } else if (strcmp(command, "exit") == 0) {
        return (exit_shell(env), 1);
    } else if (strcmp(command, "echo") == 0) {
        return (echo_command(args), 1);
    } else if (strcmp(command, "pwd") == 0) {
        return (print_working_directory(), 1);
    } else if (strcmp(command, "env") == 0) {
        return (print_environment(env), 1);
    } else if (strncmp(command, "export", 7) == 0) {
        return (export_variable(&env, args), 1);
    } else if (strncmp(command, "unset", 5) == 0) {
        return (unset_variable(&env, args), 1);
    } else {
        return 0;
    }
}

void process_shell(char **env) {
    char *input;
    t_linked_list *parsed_list;

    // 履歴リストの初期化
    History *history = init_history(MAX_HISTORY);

    // 履歴ファイルの読み込み
    load_history_from_file(HISTORY_FILE, history);

    while (1) {
        // プロンプト表示と入力受付
        input = readline("minishell> ");
        if (!input) { // EOFやエラー時の終了処理
            printf("exit\n");
            break;
        }
        if (*input) { // 入力が空でない場合
            add_history(input);           // readline用の履歴に追加
            add_to_history(history, input); // 自前の履歴にも追加
        }

        // パーサーの実行
        parsed_list = parser(input);
        if (!parsed_list) {
            fprintf(stderr, "Error: Failed to parse input.\n");
            free(input);
            continue; // 次の入力を待つ
        }

        // リストからコマンドと引数を取得
        char *command = parsed_list->content; // コマンド部分
        char *args = parsed_list->next ? parsed_list->next->content : NULL; // 引数部分

        // 内部コマンドの処理を外だし関数で呼び出す
        if (!handle_internal_commands(command, args, env))
        {
            // 外部コマンドの処理
            execute_command(parsed_list);
        }

        // メモリ解放
        linked_list_free(parsed_list);
        free(input); // 動的メモリの解放
    }

    // 履歴を保存
    save_history_to_file(HISTORY_FILE, history);

    // メモリ解放
    free_history(history);
    rl_clear_history();
}

int main(int argc, char **argv, char **envp) {
    (void)argc; // argc を無視
    (void)argv; // argv を無視
    process_shell(envp); // 入力受付関数を呼び出し
    return 0;
}


