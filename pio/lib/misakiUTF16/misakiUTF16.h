//
// misakiUTF16.h 美咲フォントドライバ ヘッダーファイル v1.1B by たま吉さん 2016/03/15
// 内部フラッシュメモリバージョン
//
// 2016/03/16 全角小文字英数字の不具合対応
// 2016/07/05 getFontData()関数の追加
// 2016/07/10 getFontTableAddress()関数の追加, fdata[],ftable[]の公開禁止
// 2016/08/07 getFontData()に半角=>全角変換指定を追加
// 2016/08/19 charUFT8toUTF16()の引数を変更
//

#ifndef misakiUTF16_h
#define misakiUTF16_h

//#include <avr/pgmspace.h>
#include <pgmspace.h>
#include <Arduino.h>

#define FTABLESIZE     1710      // フォントテーブルデータサイズ
#define FONT_LEN       8         // 1フォントのバイト数

int findcode(uint16_t  ucode) ;								    // フォントコード検索
boolean getFontDataByUTF16(byte* fontdata, uint16_t utf16) ;	// UTF16に対応する美咲フォントデータ8バイトを取得
uint16_t hkana2kana(uint16_t ucode);				        	// 半角カナを全角に変換
uint16_t utf16_HantoZen(uint16_t utf16); 				      	// UTF16半角コードをUTF16全角コードに変換
byte charUFT8toUTF16(uint16_t *pUTF16, char *pUTF8);		    // UTF8文字(1～3バイ)をUTF16に変換
byte Utf8ToUtf16(uint16_t* pUTF16, char *pUTF8);				// UTF8文字列をUTF16文字列に変換

const char* getFontData(byte* fontdata, const char *pUTF8,bool h2z=false, uint8_t *n=0);   // フォントデータ取得
const uint8_t*  getFontTableAddress();						    // フォントデータテーブル先頭アドレス取得

boolean isHankaku(uint16_t ucode);
#endif
