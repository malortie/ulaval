/**
* \file time_measure_cxx11.h
* \brief Compteur temporel permettant de mesurer le temps d'�x�cution d'un algorithme.
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/4/2015
*/

#ifndef ULAVAL_TIME_MEASURE_CXX11_H__
#define ULAVAL_TIME_MEASURE_CXX11_H__

#include <chrono>

/**
* \namespace ulaval
*
* Espace de nommage regroupant les d�finitions
* pour tous les utilitaires a �tre utilis�s dans les
* cours n�cessitant le langage c++.
*/
namespace ulaval
{

/**
* \class Compteur
*
* \brief classe g�nerique permettant de mesurer un interval de temps.
*
*/

template<typename T, typename Ratio = std::milli, typename Duration = std::chrono::duration<T, Ratio>>
class CompteurTemporel
{
	/**
	* \typedef typedef CompteurTemporel<T, Ratio, Duration> TypeClasseCompteur
	* \brief D�finition du type TypeClasseCompteur
	*
	* Le type TypeClasseCompteur repr�sente la classe g�nerique.
	*/
	typedef CompteurTemporel<T, Ratio, Duration> ClasseCompteurTemporel;


	/**
	* \typedef typedef std::chrono::time_point <std::chrono::system_clock> PointTemps
	* \brief D�finition du type PointTemps
	*
	* Le type PointTemps repr�sente un point dans le temps.
	*/
	typedef std::chrono::time_point <std::chrono::system_clock> PointTemps;

	/**
	* \typedef typedef std::chrono::system_clock HorlogeSysteme
	* \brief D�finition du type HorlogeSysteme
	*
	* Le type HorlogeSysteme repr�sente un raccourci de nom pour l'utilisation
	* de classe std 'std::chrono::system_clock'.
	*/
	typedef std::chrono::system_clock HorlogeSysteme;

public:

	/**
	* \brief Constructeur
	*
	* \param[in] p_active L'�tat du compteur
	*
	**/
	CompteurTemporel(const bool p_active = true) : m_active(false)
	{
		m_debut = std::chrono::time_point<std::chrono::system_clock>();
		changerEtat(p_active);
	}

	/**
	* \brief Retourne le point de temps de d�part
	*
	* \return le temps de d�part sous forme de point
	**/
	inline const PointTemps& debut() const
	{
		return m_debut;
	}

	/**
	* \brief Retourne le point de temps pr�sent
	*
	* \return le temps present sous forme de point
	**/
	inline const PointTemps present() const
	{
		return HorlogeSysteme::now();
	}

	/**
	* \brief Retourne l'�tat du compteur
	*
	* \return retourne vrai si le compteur est actif, sinon retourne faux
	*
	**/
	inline const bool& actif() const
	{
		return m_active;
	}

	/**
	* \brief Changer l'�tat du compteur.
	*
	* \param[in] p_etat L'�tat a changer.
	*
	**/
	inline void changerEtat(const bool p_etat)
	{
		m_active = p_etat;

		if (p_etat)
			m_debut = present();
	}

	/**
	* \brief Permet de d'intervertir l'�tat du compteur
	*
	**/
	inline void basculer()
	{
		changerEtat(!m_active);
	}

	/**
	* \brief Active le compteur
	*
	**/
	inline void activer()
	{
		changerEtat(true);
	}

	/**
	* \brief D�sactiver le compteur
	*
	**/
	inline void desactiver()
	{
		changerEtat(false);
	}

	/**
	* \brief Permet de r�initialiser le compteur
	*
	* \param[in] p_active L'etat du compteur
	*
	**/
	void reinitialiser(const bool p_active)
	{
		changerEtat(p_active);
	}

	/**
	* \brief Retourne la dur�e de temps ecoul�e
	*
	* \return la dur�e de type T
	*
	**/
	inline const T duree() const
	{
		return (m_active)
			? static_cast<T>(std::chrono::duration_cast<Duration>(present() - m_debut).count())
			: static_cast<T>(0);
	}

private:
	CompteurTemporel(const ClasseCompteurTemporel&);

private:
	PointTemps m_debut; /*!< Point de d�part pour la mesure du temps */
	bool m_active; /*!< �tat du compteur */
};

}

#endif // ULAVAL_TIME_MEASURE_CXX11_H__