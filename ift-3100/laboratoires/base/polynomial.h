#ifndef TP2_POLYNOMIAL_H__
#define TP2_POLYNOMIAL_H__

#include <vector>
#include <stack>

class polynomial : public std::vector<float>
{
	std::stack<float> prevconstants;

public:

	polynomial(float k)
	{
		insert(begin(), k);
	}

	polynomial(float a, float b) : polynomial(a)
	{
		insert(begin(), b);
	}

	polynomial(float a, float b, float c) : polynomial(a, b)
	{
		insert(begin(), c);
	}

	polynomial(float a, float b, float c, float d) : polynomial(a, b, c)
	{
		insert(begin(), d);
	}

	polynomial(float a, float b, float c, float d, float e) : polynomial(a, b, c, d)
	{
		insert(begin(), e);
	}

	polynomial(std::initializer_list<float>&& coefficients)
	{
		for (auto it = coefficients.begin(); it != coefficients.end(); ++it)
		{
			insert(begin(), *it);
		}
	}

	~polynomial()
	{

	}

	size_t degree() const
	{
		return this->size() - 1;
	}

	float evaluate(float x)
	{
		if (empty())
			return 0;

		float result = 0;
		size_t deg = degree();

		if (deg > 0) {
			result = front();

			for (size_t i = size() - 1; i > 0; i--)
			{
				result += at(i)* powf(x, static_cast<float>(deg));
				deg--;
			}
		}
		else
			result = front();

		return result;
	}

	void derive(const size_t times = 1)
	{
		if (empty())
			return;

		size_t i, j;
		size_t deg = 0;

		for (i = 0; i < times; i++) {
			deg	= degree();

			prevconstants.push(*begin());

			for (j = deg; j > 0; j--)
				at(j) *= j;

			erase(begin());
		}
	}

	void integrate(const size_t times = 1)
	{
		if (this->empty())
			return;

		size_t i, j;
		size_t deg = 0;

		for (i = 0; i < times; i++) {
			deg = degree();

			for (j = deg; j > 0; j--)
				at(j) *= (1.0f / (deg + 1));

			if (!prevconstants.empty()) {
				insert(begin(), prevconstants.top());
				prevconstants.pop();
			}
			else
				insert(begin(), 0);
		}
	}
};

#endif// TP2_POLYNOMIAL_H__