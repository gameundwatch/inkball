
# include <Siv3D.hpp> // OpenSiv3D v0.4.3

# include "Ball.h"

void Main()
{
	// 背景を水色にする
	Scene::SetBackground(ColorF(0.8, 0.9, 1.0));

	Array<Ball> Balls;

	while (System::Update())
	{
		//ClearPrint();

		// [A] キーが押されたら
		if (KeyA.down())
		{
			// Hello とデバッグ表示する
			Print << U"Hello!";
		}

		// ボタンが押されたら
		if (MouseL.down())
		{
			Balls << Ball();
		}

		if (MouseR.down())
		{
			if (!Balls.empty())
			{
				Balls.erase(Balls.end() - 1);
			}
		}

		for (auto& b : Balls)
		{
			for (auto& b2 : Balls)
			{
				if (b.getPos() == b2.getPos())
				{	continue;	}
				b.CollisionBall(b2);
			}
		}

		for (auto& b : Balls)
		{
			b.MoveBall();
			b.DrawBall();
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
