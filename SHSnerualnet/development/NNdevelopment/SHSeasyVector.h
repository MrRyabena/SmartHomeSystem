#pragma once

namespace shs {
	template <typename T>
	class EasyVector;
};


template <typename T>
class shs::EasyVector {
public:

	EasyVector(uint8_t size = 1) : _buf(new T(size)) {
		_ptr = _buf;
		_capacity = size;
	}

	~EasyVector() {
		delete[] _buf;
	}

	void push_back(const T& value) {
		reserve(sizeof(T));
		*(_ptr++) = value;
	}

	void reserve(uint8_t size) {
		if (_capacity - EasyVector::size() >= 0) return;
		T* nbuf = new T(_capacity + size);
		for (size_t i = 0; i < _capacity; i++) nbuf[i] = _buf[i];
		delete[] _buf;
		_ptr = nbuf + EasyVector::size();
		_buf = nbuf;
		_capacity++;
		
	}

	T* back() { return _ptr; };

	size_t size() { return static_cast<size_t>(_ptr - _buf); }


	auto& operator[](int val) {
		return _buf[val];
	}

	void clear() {
		delete[] _buf;
		_buf = new T(1);
		_ptr = _buf;
		_capacity = 1;
	}

private:
	T* _buf{};
	T* _ptr{};
	size_t _capacity{};
	

};


