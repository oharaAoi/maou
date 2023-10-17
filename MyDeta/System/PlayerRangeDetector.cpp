#include "PlayerRangeDetector.h"

PlayerRangeDetector::PlayerRangeDetector() {

}

void PlayerRangeDetector::Init() {
	b2pDis_.x = 0.0f;
	b2pDis_.y = 0.0f;

	e2pDis_.x = 0.0f;
	e2pDis_.y = 0.0f;

	unitB2pDis_.x = 0.0f;
	unitB2pDis_.y = 0.0f;

	b2pLinearCompletion_.x = 0.0f;
	b2pLinearCompletion_.y = 0.0f;

	nearBulletPos_.x = 0.0f;
	nearBulletPos_.y = 0.0f;

	b2pLength_ = 0.0f;

	nearLength_ = 0.0f;

	time_ = 0.0f;

	//デバック用(後で消す)
	verticalLine.x = 0.0f;
	verticalLine.y = 0.0f;

	vertialTheta = 0.0f;

	topLineSt.x = 0.0f;
	topLineSt.y = 0.0f;

	topLineEnd.x = 0.0f;
	topLineEnd.y = 0.0f;

	bottomLineSt.x = 0.0f;
	bottomLineSt.y = 0.0f;

	bottomLineEnd.x = 0.0f;
	bottomLineEnd.y = 0.0f;
}

//カプセルで範囲内にいるか判定する
void PlayerRangeDetector::Update(Player player_, BossBullet& bossBullet_) {
	for (int i = 0; i < BossBullet::kBulletMax_; i++) {
		//bossとplayerの距離
		b2pDis_.x = player_.GetPos().x - player_.GetRangePos().x;
		b2pDis_.y = player_.GetPos().y - player_.GetRangePos().y;

		//弾との距離
		e2pDis_ = CalcVector(bossBullet_.GetPos(i), player_.GetPos());

		//bossとplayerの単位ベクトルを求める
		unitB2pDis_ = ConversionNormalizeVector(player_.GetPos(), player_.GetRangePos());

		//ボスとの距離
		b2pLength_ = CheckLength(player_.GetPos(), player_.GetRangePos());

		time_ = DotProduct(unitB2pDis_, e2pDis_) / b2pLength_;

		time_ = Clamp(time_, 0, 1);

		//線形補完
		b2pLinearCompletion_.x = (1.0f - time_) * player_.GetPos().x + time_ * player_.GetRangePos().x;
		b2pLinearCompletion_.y = (1.0f - time_) * player_.GetPos().y + time_ * player_.GetRangePos().y;

		//敵との距離(最近傍点)
		nearBulletPos_ = CalcVector(bossBullet_.GetPos(i), b2pLinearCompletion_);

		nearLength_ = CheckLength(b2pLinearCompletion_, bossBullet_.GetPos(i));

		//最近傍点がカプセルの範囲内だったら
		if (bossBullet_.GetIsShot(i) == true) {
			if (nearLength_ < player_.GetRadius() + player_.GetRangeRadius()) {
				if (bossBullet_.GetIsRange(i) == false) {
					bossBullet_.SetIsPushBacked(true, i);
					bossBullet_.SetIsRange(true, i);
				}
			} else {
				bossBullet_.SetIsRange(false, i);
			}
		}

		//=========================================================
		//デバック用(後で消す)
		verticalLine.x = -b2pDis_.y;
		verticalLine.y = b2pDis_.x;

		//垂直ベクトルの角度を求める
		vertialTheta = atan2f(verticalLine.y, verticalLine.x);

		//上のベクトル
		//(20はplayerの半径)
		topLineSt.x = player_.GetRadius() * cosf(vertialTheta) + player_.GetPos().x;
		topLineSt.y = player_.GetRadius() * sinf(vertialTheta) + player_.GetPos().y;

		topLineEnd.x = player_.GetRangeRadius() * cosf(vertialTheta) + player_.GetRangePos().x;
		topLineEnd.y = player_.GetRangeRadius() * sinf(vertialTheta) + player_.GetRangePos().y;

		//下のベクトル
		bottomLineSt.x = -player_.GetRadius() * cosf(vertialTheta) + player_.GetPos().x;
		bottomLineSt.y = -player_.GetRadius() * sinf(vertialTheta) + player_.GetPos().y;

		bottomLineEnd.x = -player_.GetRangeRadius() * cosf(vertialTheta) + player_.GetRangePos().x;
		bottomLineEnd.y = -player_.GetRangeRadius() * sinf(vertialTheta) + player_.GetRangePos().y;

	}
}

void PlayerRangeDetector::Draw() {
	Novice::DrawLine(static_cast<int>(topLineSt.x + cie_->GetOrigine().x),
		static_cast<int>(topLineSt.y + cie_->GetOrigine().y),
		static_cast<int>(topLineEnd.x + cie_->GetOrigine().x),
		static_cast<int>(topLineEnd.y + cie_->GetOrigine().y),
		0xffffffff);

	Novice::DrawLine(static_cast<int>(bottomLineSt.x + cie_->GetOrigine().x),
		static_cast<int>(bottomLineSt.y + cie_->GetOrigine().y),
		static_cast<int>(bottomLineEnd.x + cie_->GetOrigine().x),
		static_cast<int>(bottomLineEnd.y + cie_->GetOrigine().y),
		0xffffffff);
}
