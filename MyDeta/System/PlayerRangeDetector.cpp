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
void PlayerRangeDetector::Update(Vector2<float>playerPos_, Vector2<float>bulletPos_, Vector2<float>bossPos_) {
	//bossとplayerの距離
	b2pDis_.x = playerPos_.x - bossPos_.x;
	b2pDis_.y = playerPos_.y - bossPos_.y;

	//弾との距離
	e2pDis_ = CalcVector(bulletPos_, playerPos_);

	//bossとplayerの単位ベクトルを求める
	unitB2pDis_ = ConversionNormalizeVector(playerPos_, bossPos_);

	//ボスとの距離
	b2pLength_ = CheckLength(playerPos_, bossPos_);

	time_ = DotProduct(unitB2pDis_, e2pDis_) / b2pLength_;

	time_ = Clamp(time_, 0, 1);

	//線形補完
	b2pLinearCompletion_.x = (1.0f - time_) * playerPos_.x + time_ * bossPos_.x;
	b2pLinearCompletion_.y = (1.0f - time_) * playerPos_.y + time_ * bossPos_.y;

	//敵との距離(最近傍点)
	nearBulletPos_ = CalcVector(bulletPos_, b2pLinearCompletion_);

	nearLength_ = CheckLength(b2pLinearCompletion_, bulletPos_);

	//デバック用(後で消す)
	verticalLine.x = -b2pDis_.y;
	verticalLine.y = b2pDis_.x;

	//垂直ベクトルの角度を求める
	vertialTheta = atan2f(verticalLine.y, verticalLine.x);

	//上のベクトル
	topLineSt.x = 20.0f * cosf(vertialTheta) + playerPos_.x;
	topLineSt.y = 20.0f * sinf(vertialTheta) + playerPos_.y;

	topLineEnd.x = 50.0f * cosf(vertialTheta) + bossPos_.x;
	topLineEnd.y = 50.0f * sinf(vertialTheta) + bossPos_.y;

	//下のベクトル
	bottomLineSt.x = -20.0f * cosf(vertialTheta) + playerPos_.x;
	bottomLineSt.y = -20.0f * sinf(vertialTheta) + playerPos_.y;

	bottomLineEnd.x = -50.0f * cosf(vertialTheta) + bossPos_.x;
	bottomLineEnd.y = -50.0f * sinf(vertialTheta) + bossPos_.y;



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
