/**
 * \file foncteur.hpp
 *
 * \brief Fichier contenant les définitions des méthodes de \class foncteur.
 *
 * \author Marc-Antoine Lortie
 *
 * \date 06/16/15
 */

#ifndef FONCTEUR_HPP__
#define FONCTEUR_HPP__

namespace ulaval
{

namespace utilities
{

//
// Constructeurs
//

template<typename R, typename ...Args>
inline foncteur<R, Args...>::foncteur() : m_f(nullptr)
{
}

template<typename R, typename ...Args>
inline foncteur<R, Args...>::foncteur(const typename foncteur<R, Args...>::Foncteur & p_f) : m_f(p_f.m_f)
{
}

template<typename R, typename ...Args>
inline foncteur<R, Args...>::foncteur(typename foncteur<R, Args...>::F p_f) : m_f(p_f)
{
}

//
// Surcharges d'opérateurs
//

template<typename R, typename ...Args>
inline typename foncteur<R, Args...>::F foncteur<R, Args...>::operator*()
{
	return m_f;
}

template<typename R, typename ...Args>
inline R foncteur<R, Args...>::operator()(Args ...args)
{
	return m_f(args...);
}

template<typename R, typename ...Args>
inline typename foncteur<R, Args...>::Foncteur & foncteur<R, Args...>::operator=(const typename foncteur<R, Args...>::Foncteur & p_f)
{
	m_f = p_f.m_f;
	return *this;
}

template<typename R, typename ...Args>
inline typename foncteur<R, Args...>::Foncteur & foncteur<R, Args...>::operator=(typename foncteur<R, Args...>::F p_f)
{
	m_f = p_f;
	return *this;
}

} /* utilities */

} /* ulaval */

#endif /* FONCTEUR_HPP__ */