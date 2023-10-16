# WBS
// object
> Player
    移動の処理(ゆっくり→早く,速く→ゆっくり)
    風の強弱
    死亡エフェクト
    電気ゲージの表示
    オーバーヒート時の描画
    描画(リソース)
> bossBullet
    弾の発射の方向(弾幕)
    当たった時のエフェクト
    押し返す時の調整
     描画(リソース)
> boss
    waveでの敵の種類
    waveでの弾の発射
    撃破エフェクト
    当たった時のエフェクト
    難易度調整
     描画(リソース)

> scene
    title
        タイトルの作製
        キーで次のシーンに移動
    tite > tutorial || game
        シーンの遷移処理
        (game)二回目以降のチュートリアルスキップ
    tutorial
        説明文の作製
        見せ方
    tutorial > game
        次の遷移への移動方法
    game
        // object
    game > result
        playerが死んだとき
        bossが死んだとき
    result
        (マジで何も考えてなかった)
        scoreの表示とは
        scoreかtimeの表示
    result > title? game?
    次のシーンの遷移処理
        

// art
