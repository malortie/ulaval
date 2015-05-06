/**
* \file time_measure_cxx03.h
* \brief Compteur temporel permettant de mesurer le temps d'éxécution d'un algorithme.
* \author Marc-Antoine Lortie
* \version 1.0
* \date 5/5/2015
*/

#ifndef ULAVAL_TIME_MEASURE_CXX03_H__
#define ULAVAL_TIME_MEASURE_CXX03_H__

#include <time.h>
#include <math.h>

namespace ulaval
{

/**
 * \enum RatioTemporel
 * \brief Énumération d'un ratio temporel.
 *
 */
enum RatioTemporel
{
	ratio_s   = 0x0,	// secondes             (1e+0)
	ratio_ms  = 0x3,	// millisecondes	(1e+3)
	ratio_mcs = 0x6,	// microsecondes	(1e+6)
	ratio_ns  = 0x9,	// nanosecondes		(1e+9)
	ratio_ps  = 0xc,	// picosecondes		(1e+12)
};


/**
 * \class CompteurTemportel
 *
 * \brief classe génerique permettant de mesurer un interval de temps.
 *
 */
template<typename T, const enum RatioTemporel Ratio>
class CompteurTemporel
{
public:

	/**
	 * \brief Constructeur
	 *
	 * \param[in] p_active L'état du compteur
	 *
	 **/
	CompteurTemporel(const bool p_active = true)
	{
		m_debut = 0;
		changerEtat(p_active);
	}

	/**
	 * \brief Retourne le point de temps de départ
	 *
	 * \return le temps de départ sous forme de point
	 **/
	const clock_t& debut() const
	{
		return m_debut;
	}

	/**
	 * \brief Retourne le point de temps présent
	 *
	 * \return le temps present sous forme de point
	 **/
	const clock_t present() const
	{
		return clock();
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
	 * \brief Retourne la durée de temps ecoulée selon un ratio spécifique
	 *
	 * \return la durée de type T
	 *
	 *
	 *
	 **/
	inline const T duree() const
	{
		T d = present() - m_debut;

		if (m_active)
		{
			if (Ratio == ratio_ms)
			{
				// Aucune conversion nécessaire.
				// Retour automatique.
				return static_cast<T>(d);
			}
			else if (Ratio == ratio_s)
			{
				// Conversion en seconde, donc division par 1000. (1e+3)
				d *= (1.0 / CLOCKS_PER_SEC);
			}
			else
			{
				// Conversion en unité arbitraire, utilisation de
				// la base 10, élevé à la puissance (Ratio - 1).
				d *= pow(10.0, Ratio - 1);
			}
		}
		else
		{
			d = 0;
		}

		return static_cast<T>(d);
	}

private:
	CompteurTemporel(const CompteurTemporel<T, Ratio>&);

private:

	clock_t m_debut; /*!< Point de départ pour la mesure du temps */
	bool m_active; /*!< État du compteur */
};


}

#endif // TIME_MEASURE_CXX03_H__