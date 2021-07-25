
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

	Font ui_score(20, U"fonts/PixelMplus10-Regular.ttf");
	Font ui_text(20);
	Font ui_result(40, U"fonts/PixelMplus10-Regular.ttf");

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
	Vec2 SpawnPoint = Vec2(400, 400);

	int score = 0;
	int scene = 1;
	int level = 1;
	int ballwait = 0;

	while (System::Update())
	{
		ClearPrint();

		// システム
		if (scene == 1) {
			// 待機状態
			score = 0;
			level = 1;
			ballwait = 0;
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
				scene = 0;
			}
		}
		else if (scene == 0){
		// ゲーム中

			// ボタンが押されたら

			if (KeyA.down()) {
				score+= 1000;
			}

	//		if (KeyD.down() && !Balls.isEmpty()) {
	//			Balls.erase(Balls.end() - 1);
	//		}

			if (level < 10) {
				level = (score / 2000) + 1;
			}

			if (MouseR.down() && !Lines.isEmpty()) {
				Lines.erase(Lines.end() - 1);
			}

			if (Balls.size() < level + 2) {

				if (ballwait > 0) {
					ballwait -= 1;
				}
				if (ballwait == 0) {
					Balls << Ball(SpawnPoint, Vec2(Random(-1.0, 1.0), Random(-1.0, 1.0)), 1.0, Random(0, 4));
					ballwait = 1000 / level;
				}
			}

			if (Lines.size() < 3) {
				if (MouseL.up()) {
					Line_temp.setDot(Vec2(Cursor::Pos()));
					if (Line_temp.getLength() > 40.0) {
						Lines << Line_temp;
					}
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
									scene = 2;
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
		else if (scene == 2) {
		
		if (MouseL.down()) {
			scene = 1;
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

		// 線の始点の描写
		if (MouseL.pressed() && !Line_temp.isEmpty()) {
			Line_temp.drawPoint(Line_temp.get1st());
		}

		// ui表示
		if (scene == 1) {
			// 待機
			ui_text(U"LEFT CLICK TO START.").drawAt(Scene::Center(), ColorF(0.2, 0.2, 0.2, 0.5 + Periodic::Sine0_1(1s) * 0.5));
		}
		else if (scene == 0) {
			// ゲーム
			// 
			if (ballwait <= 100) {
				Circle(SpawnPoint, ballwait*ballwait /100 ).drawFrame(0, 1, Palette::Darkgreen);
			}
			// スコア表示
			ui_score(U"SCORE").draw(10, 5, Color(40, 40, 40));
			ui_score(score).draw(10, 25, Color(40, 40, 40));
		}
		else if (scene == 2) {
			// リザルト
			ui_result(U"GAME OVER").drawAt(Scene::Center() + Vec2(0, -20), Color(40, 40, 40));
			ui_result(score).drawAt(Scene::Center() + Vec2(0, 20), Color(40, 40, 40));
			ui_text(U"LEFT CLICK TO BACK.").drawAt(Scene::Center() + Vec2(0, 60), ColorF(0.2, 0.2, 0.2, 0.5 + Periodic::Sine0_1(1s) * 0.5));
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
