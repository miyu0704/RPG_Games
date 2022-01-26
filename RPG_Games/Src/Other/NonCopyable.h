#pragma once

class NonCopyable
{
protected:
	NonCopyable() = default;
	virtual ~NonCopyable() = default;

private:
	// �R���X�g���N�^.
	NonCopyable(NonCopyable& Copy) = delete;
	// ���Z�q�̃I�[�o�[���[�h '='.
	void operator=(NonCopyable Copy) = delete;
	
};