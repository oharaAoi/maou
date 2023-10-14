# WBS
// object
> Player
    死亡エフェクト
    描画
> reflection
    当たり判定
    ランダムな出現
    当たった時のエフェクト
> orbit
    当たり判定
    再度発射処理
    ランダムな出現
    当たった時のエフェクト
> boss
    waveでの弾の発射
    撃破エフェクト
    当たった時のエフェクト
    難易度調整

// system
> zoom
    カメラがzoomする
        + easing

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
    result > title? game?
    次のシーンの遷移処理
        

// art
