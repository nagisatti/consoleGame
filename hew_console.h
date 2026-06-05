// hew_console.h
// ------------------------------------------------------------
// このヘッダーは、メイン関数から初期化/終了関数だけを認識できるように
// 公開プロトタイプのみ定義します。
// ------------------------------------------------------------

#pragma once

int HEWConsoleStartup(int debug_mode);
int HEWConsoleCleanup(int debug_mode);
