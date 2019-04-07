#include <list>
#include <memory>
#include <Transform.h>

class Bone : public std::enable_shared_from_this<Bone>
{
	Transform	m_local;
	Transform	m_Tpose;

	AltMath::Matrix4f					m_globalTransform;
	std::list<std::shared_ptr<Bone>>	m_childs;
	std::shared_ptr<Bone>				m_parent;

	bool m_needUpdate = true;

public:
	Bone(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation, std::shared_ptr<Bone>& p_parent);
	Bone(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation);
	~Bone();
		
	void SetNeedUpdate(bool p_needUpdate);
	void SetLocalTransform(const AltMath::Vector3f& p_pos = AltMath::Vector3f::Zero, AltMath::Quaternion p_rot = AltMath::Quaternion::Identity());
	
	void Draw(float p_offset);
	void DrawCross(AltMath::Vector3f& p_pos, float p_offset);
	void NotifyChildToUpdate();

	std::shared_ptr<Bone>	AddChild(const AltMath::Vector3<float>& p_position, const AltMath::Quaternion& p_rotation);
	Transform				GetLocalTransform();
	AltMath::Matrix4f		GetGlobalTransform();
	AltMath::Matrix4f		GetGlobalAnimatedMesh();
	AltMath::Matrix4f		GetGlobalTpose();
	AltMath::Vector3f		GetGlobalPosition();
	std::shared_ptr<Bone>	GetParent() const;
	bool					HasParent() const;

};