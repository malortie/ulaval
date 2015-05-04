/**
 * \file ContratException.h
 * \brief Fichier contenant l'implémentation de la classe ContratException et de ses héritiers
 * \author Ludovic Trottier
 * \version 0.3
 * \date mai 2014
 */
#include "ContratException.h"
#include <sstream>

using namespace std;
/**
 * \brief Constructeur de la classe de base ContratException
 * \param[in] p_fichier chaîne de caractères représentant le fichier source dans lequel a eu lieu l'erreur
 * \param[in] p_ligne un entier représentant la ligne où a eu lieu l'erreur
 * \param[in] p_type un message décrivant l'erreur
 * \param[in] p_expression le test logique qui a échoué
 */
ContratException::ContratException(const std::string & p_fichier,
		const unsigned int & p_ligne, const std::string & p_expression,
		const std::string & p_type) :
		logic_error(""), m_expression(p_expression), m_fichier(p_fichier), m_type(
				p_type), m_ligne(p_ligne) {
	ostringstream os;
	os << endl;
	os << "Message : " << m_type << endl;
	os << "Fichier : " << m_fichier << endl;
	os << "Ligne   : " << m_ligne << endl;
	os << "Test    : " << m_expression << endl;
	m_message = os.str();
}
/**
 * \brief Construit le texte complet relié à l'exception de contrat
 * \return une chaîne de caractères correspondant à l'exception
 */
const char * ContratException::what() const throw () {
	return m_message.c_str();
}
/**
 * \brief Constructeur de la classe AssertionException \n
 *
 * Le constructeur public AssertionException(...)initialise
 * sa classe de base ContratException. On n'a pas d'attribut local. Cette
 * classe est intéressante pour son TYPE lors du traitement des exceptions.
 * \param[in] p_fichier chaîne de caractères représentant le fichier source dans lequel a eu lieu l'erreur
 * \param[in] p_ligne un entier représentant la ligne où a eu lieu l'erreur
 * \param[in] p_expression le test logique qui a échoué
 */

AssertionException::AssertionException(const std::string & p_fichier,
		const unsigned int & p_ligne, const std::string & p_expression) :
		ContratException(p_fichier, p_ligne, p_expression, "ERREUR D'ASSERTION") {
}

/**
 * \brief Constructeur de la classe PreconditionException en initialisant la classe de base ContratException.
 * 		 La classe représente l'erreur de précondition dans la théorie du contrat.
 * \param[in] p_fichier chaîne de caractères représentant le fichier source dans lequel a eu lieu l'erreur
 * \param[in] p_ligne un entier représentant la ligne où a eu lieu l'erreur
 * \param[in] p_expression le test logique qui a échoué
 */
PreconditionException::PreconditionException(const std::string & p_fichier,
		const unsigned int & p_ligne, const std::string & p_expression) :
		ContratException(p_fichier, p_ligne, p_expression, "ERREUR DE PRECONDITION") {
}
/**
 * \brief Constructeur de la classe PostconditionException en initialisant la classe de base ContratException.
 *        La classe représente des erreurs de postcondition dans la théorie du contrat.
 * \param[in] p_fichier chaîne de caractères représentant le fichier source dans lequel a eu lieu l'erreur
 * \param[in] p_ligne un entier représentant la ligne où a eu lieu l'erreur
 * \param[in] p_expression le test logique qui a échoué
 */
PostconditionException::PostconditionException(const std::string & p_fichier,
		const unsigned int & p_ligne, const std::string & p_expression) :
		ContratException(p_fichier, p_ligne, p_expression,
				"ERREUR DE POSTCONDITION") {
}

/**
 * \brief Constructeur de la classe InvariantException en initialisant la classe de base ContratException.
 * La classe représente des erreurs d'invariant dans la théorie du contrat.
 * \param[in] p_fichier chaîne de caractères représentant le fichier source dans lequel a eu lieu l'erreur
 * \param[in] p_ligne un entier représentant la ligne où a eu lieu l'erreur
 * \param[in] p_expression le test logique qui a échoué
 */
InvariantException::InvariantException(const std::string & p_fichier,
		const unsigned int & p_ligne, const std::string & p_expression) :
		ContratException(p_fichier, p_ligne, p_expression, "ERREUR D'INVARIANT") {
}

