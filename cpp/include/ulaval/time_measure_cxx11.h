/**
* \file time_measure_cxx11.h
* \brief Compteur temporel permettant de mesurer le temps d'éxécution d'un algorithme.
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
* Espace de nommage regroupant les définitions
* pour tous les utilitaires a être utilisés dans les
* cours nécessitant le langage c++.
*/
namespace ulaval
{

/**
* \class Compteur
*
* \brief classe génerique permettant de mesurer un interval de temps.
*
*/

template<typename T, typename Ratio = std::milli, typename Duration = std::chrono::duration<T, Ratio>>
class CompteurTemporel
{
	/**
	* \typedef typedef CompteurTemporel<T, Ratio, Duration> TypeClasseCompteur
	* \brief Définition du type TypeClasseCompteur
	*
	* Le type TypeClasseCompteur représente la classe génerique.
	*/
	typedef CompteurTemporel<T, Ratio, Duration> ClasseCompteurTemporel;


	/**
	* \typedef typedef std::chrono::time_point <std::chrono::system_clock> PointTemps
	* \brief Définition du type PointTemps
	*
	* Le type PointTemps représente un point dans le temps.
	*/
	typedef std::chrono::time_point <std::chrono::system_clock> PointTemps;

	/**
	* \typedef typedef std::chrono::system_clock HorlogeSysteme
	* \brief Définition du type HorlogeSysteme
	*
	* Le type HorlogeSysteme représente un raccourci de nom pour l'utilisation
	* de classe std 'std::chrono::system_clock'.
	*/
	typedef std::chrono::system_clock HorlogeSysteme;

public:

	/**
	* \brief Constructeur
	*
	* \param[in] p_active L'état du compteur
	*
	**/
	CompteurTemporel(const bool p_active = true) : m_active(false)
	{
		m_debut = std::chrono::time_point<std::chrono::system_clock>();
		changerEtat(p_active);
	}

	/**
	* \brief Retourne le point de temps de départ
	*
	* \return le temps de départ sous forme de point
	**/
	inline const PointTemps& debut() const
	{
		return m_debut;
	}

	/**
	* \brief Retourne le point de temps présent
	*
	* \return le temps present sous forme de point
	**/
	inline const PointTemps present() const
	{
		return HorlogeSysteme::now();
	}

	/**
	* \brief Retourne l'état du compteur
	*
	* \return retourne vrai si le compteur est actif, sinon retourne faux
	*
	**/
	inline const bool& actif() const
	{
		return m_active;
	}

	/**
	* \brief Changer l'état du compteur.
	*
	* \param[in] p_etat L'état a changer.
	*
	**/
	inline void changerEtat(const bool p_etat)
	{
		m_active = p_etat;

		if (p_etat)
			m_debut = present();
	}

	/**
	* \brief Permet de d'intervertir l'état du compteur
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
	* \brief Désactiver le compteur
	*
	**/
	inline void desactiver()
	{
		changerEtat(false);
	}

	/**
	* \brief Permet de réinitialiser le compteur
	*
	* \param[in] p_active L'etat du compteur
	*
	**/
	void reinitialiser(const bool p_active)
	{
		changerEtat(p_active);
	}

	/**
	* \brief Retourne la durée de temps ecoulée
	*
	* \return la durée de type T
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
	PointTemps m_debut; /*!< Point de départ pour la mesure du temps */
	bool m_active; /*!< État du compteur */
};

}

#endif // ULAVAL_TIME_MEASURE_CXX11_H__