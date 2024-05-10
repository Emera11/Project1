#pragma once
#include <iostream>
#include <string>
#include<vector>
#include<DxLib.h>



class Debug {
    std::vector<std::string> List; //�`�悷�鍀��
    int FontHandle; //�`�悷��t�H���g
public:
    void Init() { //�t�H���g���g�p���Ȃ��ꍇ�͂���Ȃ�
        FontHandle = CreateFontToHandle("�l�r�S�V�b�N", 16, 2);
    }

    void Add(std::string text) { //�`�悷�鍀�ڂ�ǉ�
        List.push_back(text);
    }

    void Add() { //��s��ǉ�
        List.push_back("");
    }

    void Update() {
        int i = 0;
        for (auto& t : List) {
            if (t == "") { //��s����
                i++;
                continue;
            }
            int x, y, l;
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127); //�w�i�̋�`�𔼓����ɂ���
            GetDrawStringSizeToHandle(&x, &y, &l, t.c_str(), t.length(), FontHandle); //�e�s�̑傫�����擾
            DrawBox(0, i * y, x, i * y + y, 0x000000, TRUE); //�w�i�̋�`��`��
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //����������ʏ�ɖ߂�
            DrawStringToHandle(0, i * y, t.c_str(), 0xffffff, FontHandle); //��������t�H���g���g���ĕ`��

            i++;
        }
        List.clear(); //���ׂĕ`�悵�I������A���X�g����������
    }
};

Debug debug;