﻿
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

# include "Ball.h"
# include "Block.h"
# include "Ink.h"

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));
	Scene::Resize(800, 800);
	Window::Resize(800, 800);

	Font ui_score(40);
	Font ui_text(20);

	Array<Ball> Balls;
	Array<Ink>	Lines;
	Ink Line_temp;
	Grid<int>	Stage = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,15,0,0,0,0,0,1,1,0,0,0,0,0,14,0,0,1},
		{1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,13,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	}; // 40 X 40 rectangle,

	int score = 0;
	bool wait = true;

	while (System::Update())
	{
		// ClearPrint();

		// システム
		if (wait) {
			// 待機状態
			score = 0;
			if (!Balls.empty()) {
				Balls.clear();
			}
			if (!Lines.empty()) {
				Lines.clear();
			}
			if (!Balls.empty()) {
				Balls.clear();
			}
			if (MouseL.down()) {
				wait = false;
			}
		}
		else {
		// ゲーム中

			// ボタンが押されたら
			if (KeyA.down()) {
				Balls << Ball();
			}

			if (KeyD.down() && !Balls.isEmpty()) {
				Balls.erase(Balls.end() - 1);
			}

			if (MouseR.down() && !Lines.isEmpty()) {
				Lines.erase(Lines.end() - 1);
			}

			if (Lines.size() < 3) {
				if (MouseL.up()) {
					Line_temp.setDot(Vec2(Cursor::Pos()));
					Lines << Line_temp;
					Line_temp.Clear();
				}
				if (MouseL.down()) {
					Line_temp.setDot(Vec2(Cursor::Pos()));
				}
			}

			// ボール挙動
			
			for (auto bal = Balls.begin(); bal != Balls.end(); ++bal) {
				bal->moveBall();
				for (auto& bal2 : Balls) {
					if (bal->getPos() == bal2.getPos()) {
						continue;
					}
					bal->collisionBall(bal2);
				}

				for (auto y : step(Stage.height())) {
					for (auto x : step(Stage.width())) {
						Block blk(y, x, Stage[y][x]);
						bal->collisionBlock(blk);
					}
				}

				for (auto lin = Lines.begin(); lin != Lines.end(); ++lin) {
					if (bal->collisionLine(*lin)) {
						Lines.erase(lin);
						break;
					}
				}
			}
			
			// ボールが穴に入る挙動
			for (int y : step(Stage.height())) {
				for (int x : step(Stage.width())) {
					Block blk(y, x, Stage[y][x]);
					if (Stage[y][x] >= 10) {
						blk.setHall(y, x);
						for (auto bal = Balls.begin(); bal != Balls.end(); ) {
						bal->attractHall(y, x);
							if (bal->collisionHall(y, x)) {
								if (bal->addScore(blk) >= 0) {
									score += bal->addScore(blk);
								}
								else {
									wait = true;
								}
							bal = Balls.erase(bal);
							}
							else {
								bal++;
							}
						}
					}
				}
			}
			

			// インク本体
			for (auto& lin : Lines) {
				lin.makeLine();
			}

		}


		//描写
		// ブロック描写 
		for (auto y : step(Stage.height())) {
			for (auto x : step(Stage.width())) {
				Block blk(y, x, Stage[y][x]);
				blk.drawBlock(y, x);
			}
		}

		// ボール描写
		for (auto& bal : Balls) {
			bal.drawBall();
		}

		// インク描写
		for (auto& lin : Lines) {
			lin.drawLine();
		}

		// ui表示
		if (wait) {
			ui_text(U"LEFT CLICK TO START.").drawAt(Scene::Center(), ColorF(0.2, 0.2, 0.2, 0.5 + Periodic::Sine0_1(1s) * 0.5));
		}
		else {
			// スコア表示
			ui_score(score).draw(20, 20, Color(40, 40, 40));
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
