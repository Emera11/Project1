#pragma once
#include <iostream>
#include <string>
#include<vector>
#include<DxLib.h>



class Debug {
    std::vector<std::string> List; //描画する項目
    int FontHandle; //描画するフォント
public:
    void Init() { //フォントを使用しない場合はいらない
        FontHandle = CreateFontToHandle("ＭＳゴシック", 16, 2);
    }

    void Add(std::string text) { //描画する項目を追加
        List.push_back(text);
    }

    void Add() { //空行を追加
        List.push_back("");
    }

    void Update() {
        int i = 0;
        for (auto& t : List) {
            if (t == "") { //空行処理
                i++;
                continue;
            }
            int x, y, l;
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127); //背景の矩形を半透明にする
            GetDrawStringSizeToHandle(&x, &y, &l, t.c_str(), t.length(), FontHandle); //各行の大きさを取得
            DrawBox(0, i * y, x, i * y + y, 0x000000, TRUE); //背景の矩形を描画
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //半透明から通常に戻す
            DrawStringToHandle(0, i * y, t.c_str(), 0xffffff, FontHandle); //文字列をフォントを使って描画

            i++;
        }
        List.clear(); //すべて描画し終えたら、リストを消去する
    }
};

Debug debug;