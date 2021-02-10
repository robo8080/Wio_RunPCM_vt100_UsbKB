#ifndef ROMANCONV_H
#define ROMANCONV_H

// ローマ字変換用
bool isConvert = false; // 変換中か？
uint8_t rLen   = 0;     // 変換位置
char rBuf[5]   = {};    // ローマ字入力バッファ

// 母音テーブル
PROGMEM const char VOWEL_TBL[] = "aiueon";

// 文字変換テーブル
PROGMEM const char CONV_TBL[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA2, 0xA3, 0x00, 0xA5, 0xA4, 0xB0, 0xA1, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
  0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// ローマ字変換辞書
PROGMEM const char CONV_DIC[] = {
/*-----+-----+-----+-----------+-----------+-----------+-----------+-----------+-----+-----+
 | 1st | 2nd | 3rd | a         | i         | u         | e         | o         | n   | VSM |
 +-----+-----+-----+-----------+-----------+-----------+-----------+-----------+-----+-----*/
  0x00, 0x00, 0x00, 0xB1, 0x00, 0xB2, 0x00, 0xB3, 0x00, 0xB4, 0x00, 0xB5, 0x00, 0x00, 0x00,
  'b' , 0x00, 0x00, 0xCA, 0x00, 0xCB, 0x00, 0xCC, 0x00, 0xCD, 0x00, 0xCE, 0x00, 0x00, 0xDE,
  'b' , 'y' , 0x00, 0xCB, 0xAC, 0xCB, 0xA8, 0xCB, 0xAD, 0xCB, 0xAA, 0xCB, 0xAE, 0x00, 0xDE,
  'c' , 0x00, 0x00, 0xB6, 0x00, 0xBC, 0x00, 0xB8, 0x00, 0xBE, 0x00, 0xBA, 0x00, 0x00, 0x00,
  'c' , 'h' , 0x00, 0xC1, 0xAC, 0xC1, 0xA8, 0xC1, 0x00, 0xC1, 0xAA, 0xC1, 0xAE, 0x00, 0x00,
  'c' , 'y' , 0x00, 0xC1, 0xAC, 0xC1, 0xA8, 0xC1, 0xAD, 0xC1, 0xAA, 0xC1, 0xAE, 0x00, 0x00,
  'd' , 0x00, 0x00, 0xC0, 0x00, 0xC1, 0x00, 0xC2, 0x00, 0xC3, 0x00, 0xC4, 0x00, 0x00, 0xDE,
  'd' , 'h' , 0x00, 0xC3, 0xAC, 0xC3, 0xA8, 0xC3, 0xAD, 0xC3, 0xAA, 0xC3, 0xAE, 0x00, 0xDE,
  'd' , 'w' , 0x00, 0xC4, 0xA7, 0xC4, 0xA8, 0xC4, 0xA9, 0xC4, 0xAA, 0xC4, 0xAB, 0x00, 0xDE,
  'd' , 'y' , 0x00, 0xC1, 0xAC, 0xC1, 0xA8, 0xC1, 0xAD, 0xC1, 0xAA, 0xC1, 0xAE, 0x00, 0xDE,
  'f' , 0x00, 0x00, 0xCC, 0xA7, 0xCC, 0xA8, 0xCC, 0x00, 0xCC, 0xAA, 0xCC, 0xAB, 0x00, 0x00,
  'f' , 'w' , 0x00, 0xCC, 0xA7, 0xCC, 0xA8, 0xCC, 0xA9, 0xCC, 0xAA, 0xCC, 0xAB, 0x00, 0x00,
  'f' , 'y' , 0x00, 0xCC, 0xAC, 0xCC, 0xA8, 0xCC, 0xAD, 0xCC, 0xAA, 0xCC, 0xAE, 0x00, 0x00,
  'g' , 0x00, 0x00, 0xB6, 0x00, 0xB7, 0x00, 0xB8, 0x00, 0xB9, 0x00, 0xBA, 0x00, 0x00, 0xDE,
  'g' , 'w' , 0x00, 0xB8, 0xA7, 0xB8, 0xA8, 0xB8, 0xA9, 0xB8, 0xAA, 0xB8, 0xAB, 0x00, 0xDE,
  'g' , 'y' , 0x00, 0xB7, 0xAC, 0xB7, 0xA8, 0xB7, 0xAD, 0xB7, 0xAA, 0xB7, 0xAE, 0x00, 0xDE,
  'h' , 0x00, 0x00, 0xCA, 0x00, 0xCB, 0x00, 0xCC, 0x00, 0xCD, 0x00, 0xCE, 0x00, 0x00, 0x00,
  'h' , 'y' , 0x00, 0xCB, 0xAC, 0xCB, 0xA8, 0xCB, 0xAD, 0xCB, 0xAA, 0xCB, 0xAE, 0x00, 0x00,
  'j' , 0x00, 0x00, 0xBC, 0xAC, 0xBC, 0x00, 0xBC, 0xAD, 0xBC, 0xAA, 0xBC, 0xAE, 0x00, 0xDE,
  'j' , 'y' , 0x00, 0xBC, 0xAC, 0xBC, 0xA8, 0xBC, 0xAD, 0xBC, 0xAA, 0xBC, 0xAE, 0x00, 0xDE,
  'k' , 0x00, 0x00, 0xB6, 0x00, 0xB7, 0x00, 0xB8, 0x00, 0xB9, 0x00, 0xBA, 0x00, 0x00, 0x00,
  'k' , 'w' , 0x00, 0xB8, 0xA7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  'k' , 'y' , 0x00, 0xB7, 0xAC, 0xB7, 0xA8, 0xB7, 0xAD, 0xB7, 0xAA, 0xB7, 0xAE, 0x00, 0x00,
  'l' , 0x00, 0x00, 0xA7, 0x00, 0xA8, 0x00, 0xA9, 0x00, 0xAA, 0x00, 0xAB, 0x00, 0x00, 0x00,
  'l' , 't' , 0x00, 0x00, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  'l' , 't' , 's' , 0x00, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  'l' , 'y' , 0x00, 0xAC, 0x00, 0xA8, 0x00, 0xAD, 0x00, 0xAA, 0x00, 0xAE, 0x00, 0x00, 0x00,
  'm' , 0x00, 0x00, 0xCF, 0x00, 0xD0, 0x00, 0xD1, 0x00, 0xD2, 0x00, 0xD3, 0x00, 0x00, 0x00,
  'm' , 'y' , 0x00, 0xD0, 0xAC, 0xD0, 0xA8, 0xD0, 0xAD, 0xD0, 0xAA, 0xD0, 0xAE, 0x00, 0x00,
  'n' , 0x00, 0x00, 0xC5, 0x00, 0xC6, 0x00, 0xC7, 0x00, 0xC8, 0x00, 0xC9, 0x00, 0xDD, 0x00,
  'n' , 'g' , 0x00, 0xB6, 0x00, 0xB7, 0x00, 0xB8, 0x00, 0xB9, 0x00, 0xBA, 0x00, 0x00, 0xDF,
  'n' , 'y' , 0x00, 0xC6, 0xAC, 0xC6, 0xA8, 0xC6, 0xAD, 0xC6, 0xAA, 0xC6, 0xAE, 0x00, 0x00,
  'p' , 0x00, 0x00, 0xCA, 0x00, 0xCB, 0x00, 0xCC, 0x00, 0xCD, 0x00, 0xCE, 0x00, 0x00, 0xDF,
  'p' , 'y' , 0x00, 0xCB, 0xAC, 0xCB, 0xA8, 0xCB, 0xAD, 0xCB, 0xAA, 0xCB, 0xAE, 0x00, 0xDF,
  'q' , 0x00, 0x00, 0xB8, 0xA7, 0xB8, 0xA8, 0xB8, 0x00, 0xB8, 0xAA, 0xB8, 0xAB, 0x00, 0x00,
  'q' , 'w' , 0x00, 0xB8, 0xA7, 0xB8, 0xA8, 0xB8, 0xA9, 0xB8, 0xAA, 0xB8, 0xAB, 0x00, 0x00,
  'q' , 'y' , 0x00, 0xB8, 0xAC, 0xB8, 0xA8, 0xB8, 0xAD, 0xB8, 0xAA, 0xB8, 0xAE, 0x00, 0x00,
  'r' , 0x00, 0x00, 0xD7, 0x00, 0xD8, 0x00, 0xD9, 0x00, 0xDA, 0x00, 0xDB, 0x00, 0x00, 0x00,
  'r' , 'y' , 0x00, 0xD8, 0xAC, 0xD8, 0xA8, 0xD8, 0xAD, 0xD8, 0xAA, 0xD8, 0xAE, 0x00, 0x00,
  's' , 0x00, 0x00, 0xBB, 0x00, 0xBC, 0x00, 0xBD, 0x00, 0xBE, 0x00, 0xBF, 0x00, 0x00, 0x00,
  's' , 'h' , 0x00, 0xBC, 0xAC, 0xBC, 0x00, 0xBC, 0xAD, 0xBC, 0xAA, 0xBC, 0xAE, 0x00, 0x00,
  's' , 'y' , 0x00, 0xBC, 0xAC, 0xBC, 0xA8, 0xBC, 0xAD, 0xBC, 0xAA, 0xBC, 0xAE, 0x00, 0x00,
  's' , 'w' , 0x00, 0xBD, 0xA7, 0xBD, 0xA8, 0xBD, 0xA9, 0xBD, 0xAA, 0xBD, 0xAB, 0x00, 0x00,
  't' , 0x00, 0x00, 0xC0, 0x00, 0xC1, 0x00, 0xC2, 0x00, 0xC3, 0x00, 0xC4, 0x00, 0x00, 0x00,
  't' , 's' , 0x00, 0xC2, 0xA7, 0xC2, 0xA8, 0xC2, 0x00, 0xC2, 0xAA, 0xC2, 0xAB, 0x00, 0x00,
  't' , 'w' , 0x00, 0xC4, 0xA7, 0xC4, 0xA8, 0xC4, 0xA9, 0xC4, 0xAA, 0xC4, 0xAB, 0x00, 0x00,
  't' , 'y' , 0x00, 0xC1, 0xAC, 0xC1, 0xA8, 0xC1, 0xAD, 0xC1, 0xAA, 0xC1, 0xAE, 0x00, 0x00,
  'v' , 0x00, 0x00, 0xB3, 0xA7, 0xB3, 0xA8, 0xB3, 0x00, 0xB3, 0xAA, 0xB3, 0xAB, 0x00, 0xDE,
  'v' , 'y' , 0x00, 0xB3, 0xAC, 0xB3, 0xA8, 0xB3, 0xAD, 0xB3, 0xAA, 0xB3, 0xAE, 0x00, 0xDE,
  'w' , 0x00, 0x00, 0xDC, 0x00, 0xB3, 0xA8, 0xB3, 0x00, 0xB3, 0xAA, 0xA6, 0x00, 0x00, 0x00,
  'w' , 'h' , 0x00, 0xB3, 0xA7, 0xB3, 0xA8, 0xB3, 0x00, 0xB3, 0xAA, 0xB3, 0xAB, 0x00, 0x00,
  'x' , 0x00, 0x00, 0xA7, 0x00, 0xA8, 0x00, 0xA9, 0x00, 0xAA, 0x00, 0xAB, 0x00, 0xDD, 0x00,
  'x' , 't' , 0x00, 0x00, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  'x' , 't' , 's' , 0x00, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  'x' , 'y' , 0x00, 0xAC, 0x00, 0xA8, 0x00, 0xAD, 0x00, 0xAA, 0x00, 0xAE, 0x00, 0x00, 0x00,
  'y' , 0x00, 0x00, 0xD4, 0x00, 0xB2, 0x00, 0xD5, 0x00, 0xB4, 0x00, 0xD6, 0x00, 0x00, 0x00,
  'z' , 0x00, 0x00, 0xBB, 0x00, 0xBC, 0x00, 0xBD, 0x00, 0xBE, 0x00, 0xBF, 0x00, 0x00, 0xDE,
  'z' , 'y' , 0x00, 0xBC, 0xAC, 0xBC, 0xA8, 0xBC, 0xAD, 0xBC, 0xAA, 0xBC, 0xAE, 0x00, 0xDE,
};
PROGMEM const int DIC_CNT = sizeof(CONV_DIC) / sizeof(CONV_DIC[0]) / 15;

// 変換後の文字をキューに入れる
void pushKana(const uint8_t c) {
  xQueueSend(xQueue, &c, 0);
}

// カナ変換
uint8_t toKana(const uint8_t ch) {
  if (!isConvert || ch < 0x20 || ch > 0x7E) {
    rLen = 0;
    return (ch);
  }
  uint8_t c = CONV_TBL[ch];
  if (!c) {
    rLen = 0;
    return (ch);
  }
  if ((c < 'a') || (c > 'z')) {
    rLen = 0;
    pushKana(c);
    return (0);
  }

  if (rLen > 3) rLen = 0;
  rBuf[rLen] = 0x00;
  int idx = strchr(VOWEL_TBL, c) - VOWEL_TBL;
  if ((idx < 0) || ((rLen == 0) && (idx == 5))) {
    rBuf[rLen++] = c;
  } else {
    for (int i = 0; i < DIC_CNT; i++) {
      const char *arr = &CONV_DIC[i * 15];
      int flg = strncmp(arr, rBuf, rLen + 1);
      if (flg == 0) {
        if (arr[idx * 2 + 3]) {
          pushKana(arr[idx * 2 + 3]);
          if (arr[14])           
            pushKana(arr[14]);
          if (arr[idx * 2 + 4]) 
            pushKana(arr[idx * 2 + 4]);
        }
        break;
      } else if (flg > 0) {
        break;
      }
    }
    rLen = 0;
  }
  return (0);
}

#endif
