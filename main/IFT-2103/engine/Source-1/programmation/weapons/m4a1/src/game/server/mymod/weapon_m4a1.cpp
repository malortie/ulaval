//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Basic example of a rifle weapon (M4A1) 
//
//=============================================================================//

#include "cbase.h"
#include "basehlcombatweapon.h"
#include "npcevent.h"
#include "basecombatcharacter.h"
#include "ai_basenpc.h"
#include "player.h"
#include "game.h"
#include "in_buttons.h"
#include "ai_memory.h"
#include "soundent.h"
#include "rumble_shared.h"
#include "gamestats.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// CWeaponM4A1
//-----------------------------------------------------------------------------
class CWeaponM4A1 : public CHLSelectFireMachineGun
{
	DECLARE_DATADESC();
public:
	DECLARE_CLASS(CWeaponM4A1, CHLSelectFireMachineGun);

	CWeaponM4A1();

	DECLARE_SERVERCLASS();

	virtual Activity GetDrawActivity(void);
	virtual bool	Deploy(void);
	virtual bool	Holster(CBaseCombatWeapon *pSwitchingTo);

	void			AddViewKick(void);
	void			PrimaryAttack(void);
	void			SecondaryAttack(void);

	int				GetMinBurst();
	int				GetMaxBurst();

	bool			Reload(void);
	void			WeaponIdle(void);

	virtual void	ItemPostFrame(void);

	float			GetFireRate(void);
	int				CapabilitiesGet(void);
	Activity		GetPrimaryAttackActivity(void);

	virtual const Vector& GetBulletSpread(void);

	const WeaponProficiencyInfo_t *GetProficiencyValues();

	// Returns true if the silencer is attached.
	const bool&	IsSilencerOn( void ) const;

	// Toggle silencer status.
	void		ToggleSilencer( void );

	// Attach the silencer.
	void		AttachSilencer( void );

	// Detach the silencer.
	void		DetachSilencer( void );

protected:

	// Update silencer status.
	void		UpdateSilencer( void );

private:
	// Is silencer attached or detached?
	bool m_bSilencerOn;

	// Are we attaching the silencer?
	bool m_bTogglingSilencer;
};

//
// Server side implementation of the weapon.
//
IMPLEMENT_SERVERCLASS_ST(CWeaponM4A1, DT_WeaponM4A1)
END_SEND_TABLE()

//
// Link the weapon class.
//
LINK_ENTITY_TO_CLASS(weapon_m4a1, CWeaponM4A1);
PRECACHE_WEAPON_REGISTER(weapon_m4a1);

//
// Weapon data table.
//
BEGIN_DATADESC(CWeaponM4A1)
	DEFINE_FIELD(m_bSilencerOn, FIELD_BOOLEAN),
	DEFINE_FIELD(m_bTogglingSilencer, FIELD_BOOLEAN),
END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponM4A1::CWeaponM4A1()
{
	m_fMinRange1 = 0;// No minimum range. 
	m_fMaxRange1 = 1400;

	m_bAltFiresUnderwater	= false;
	m_bSilencerOn			= false;
	m_bTogglingSilencer		= false;
}

//-----------------------------------------------------------------------------
// Purpose: Returns the ideal draw activity.
//-----------------------------------------------------------------------------
Activity CWeaponM4A1::GetDrawActivity(void)
{
	return !m_bSilencerOn 
		? ACT_VM_DRAW 
		: ACT_VM_DRAW_SILENCED;
}

//-----------------------------------------------------------------------------
// Purpose: Called when the weapon is drawn.
//-----------------------------------------------------------------------------
bool CWeaponM4A1::Deploy(void)
{
	bool fRet = BaseClass::Deploy();

	if ( fRet )
	{
		ConVarRef fov("viewmodel_fov");
		fov.SetValue(72);

		m_bTogglingSilencer = false;
	}

	return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: Called when switching to a different weapon.
//-----------------------------------------------------------------------------
bool CWeaponM4A1::Holster(CBaseCombatWeapon *pSwitchingTo)
{
	// Call base class to ensure that holster operations are
	// correctly done.
	bool fRet = BaseClass::Holster(pSwitchingTo);

	if (fRet)
	{
		// Revert the viewmodel FOV to it's default value. 
		ConVarRef fov("viewmodel_fov");
		fov.SetValue(fov.GetDefault());

		// If we were attaching/detaching the silencer, cancel the
		// toggle state.
		m_bTogglingSilencer = false;
	}

	return fRet;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Output : Activity
//-----------------------------------------------------------------------------
Activity CWeaponM4A1::GetPrimaryAttackActivity(void)
{
	// Play the regular primary attack activity, unless the
	// silencer is attached.
	return !m_bSilencerOn 
		? ACT_VM_PRIMARYATTACK 
		: ACT_VM_PRIMARYATTACK_SILENCED;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
const Vector& CWeaponM4A1::GetBulletSpread(void)
{
	static const Vector cone = VECTOR_CONE_5DEGREES;
	return cone;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CWeaponM4A1::Reload(void)
{
	// Call base reload method.
	//
	// Make sure to play the appropriate reload activity.
	// If the silencer is detached, play the regular activity,
	// otherwise play the 'silenced' activity.
	// 
	return DefaultReload(GetMaxClip1(), GetMaxClip2(), !m_bSilencerOn ? ACT_VM_RELOAD : ACT_VM_RELOAD_SILENCED);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CWeaponM4A1::WeaponIdle(void)
{
	//Idle again if we've finished
	if (HasWeaponIdleTimeElapsed())
	{
		// Play the appropriate idle activity.
		// If the silencer is attached, play the 'silenced' activity,
		// otherwise play the default one.
		SendWeaponAnim(!m_bSilencerOn ? ACT_VM_IDLE : ACT_VM_IDLE_SILENCED);
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CWeaponM4A1::ItemPostFrame(void)
{
	// Check the silencer status.
	UpdateSilencer();

	// Call base class ItemPostFrame.
	BaseClass::ItemPostFrame();
}

//-----------------------------------------------------------------------------
// Purpose: Weapon fire rate.
//-----------------------------------------------------------------------------
float CWeaponM4A1::GetFireRate(void)
{ 
	return 0.075f; // 13.3hz
}

//-----------------------------------------------------------------------------
// Purpose: Obtain the weapon capabilities.
//-----------------------------------------------------------------------------
int	CWeaponM4A1::CapabilitiesGet(void)
{
	// This weapon has a primary range attack capability.
	return bits_CAP_WEAPON_RANGE_ATTACK1;
}

//-----------------------------------------------------------------------------
// Purpose: Shake the screen when firing.
//-----------------------------------------------------------------------------
void CWeaponM4A1::AddViewKick(void)
{
#define	EASY_DAMPEN			0.5f
#define	MAX_VERTICAL_KICK	1.0f	//Degrees
#define	SLIDE_LIMIT			2.0f	//Seconds

	//Get the view kick
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

	if (pPlayer == NULL)
		return;

	DoMachineGunKick(pPlayer, EASY_DAMPEN, MAX_VERTICAL_KICK, m_fFireDuration, SLIDE_LIMIT);
}


//-----------------------------------------------------------------------------
// Purpose: Primary attack
//-----------------------------------------------------------------------------
void CWeaponM4A1::PrimaryAttack(void)
{
	// Only the player fires this way so we can cast
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());
	if (!pPlayer)
		return;

	// Abort here to handle burst and auto fire modes
	if ((UsesClipsForAmmo1() && m_iClip1 == 0) || (!UsesClipsForAmmo1() && !pPlayer->GetAmmoCount(m_iPrimaryAmmoType)))
		return;

	m_nShotsFired++;

	// Do a muzzleflash effect.
	pPlayer->DoMuzzleFlash();

	// To make the firing framerate independent, we may have to fire more than one bullet here on low-framerate systems, 
	// especially if the weapon we're firing has a really fast rate of fire.
	int iBulletsToFire = 0;
	float fireRate = GetFireRate();

	// MUST call sound before removing a round from the clip of a CHLMachineGun
	while (m_flNextPrimaryAttack <= gpGlobals->curtime)
	{
		WeaponSound(!m_bSilencerOn ? SINGLE : SPECIAL1, m_flNextPrimaryAttack);
		m_flNextPrimaryAttack = m_flNextPrimaryAttack + fireRate;
		iBulletsToFire++;
	}

	// Make sure we don't fire more than the amount in the clip, if this weapon uses clips
	if (UsesClipsForAmmo1())
	{
		if (iBulletsToFire > m_iClip1)
			iBulletsToFire = m_iClip1;
		m_iClip1 -= iBulletsToFire;
	}

	m_iPrimaryAttacks++;
	gamestats->Event_WeaponFired(pPlayer, true, GetClassname());

	// Fire the bullets
	FireBulletsInfo_t info;
	info.m_iShots = iBulletsToFire;
	info.m_vecSrc = pPlayer->Weapon_ShootPosition();
	info.m_vecDirShooting = pPlayer->GetAutoaimVector(AUTOAIM_SCALE_DEFAULT);
	info.m_vecSpread = pPlayer->GetAttackSpread(this);
	info.m_flDistance = MAX_TRACE_LENGTH;
	info.m_iAmmoType = m_iPrimaryAmmoType;
	info.m_iTracerFreq = 2;
	FireBullets(info);

	//Factor in the view kick
	AddViewKick();

	CSoundEnt::InsertSound(SOUND_COMBAT, GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN, 0.2, pPlayer);

	SendWeaponAnim(GetPrimaryAttackActivity());
	pPlayer->SetAnimation(PLAYER_ATTACK1);

	// Register a muzzleflash for the AI
	pPlayer->SetMuzzleFlashTime(gpGlobals->curtime + 0.5);
}


//-----------------------------------------------------------------------------
// Purpose: Secondary attack.
//-----------------------------------------------------------------------------
void CWeaponM4A1::SecondaryAttack(void)
{
	// Only the player fires this way so we can cast
	CBasePlayer *pPlayer = ToBasePlayer(GetOwner());

	// Ensure the player is the owner and is valid.
	if (pPlayer == NULL)
		return;

	// Do not try to attach/detach the silencer if we are reloading.
	if (m_bInReload)
		return;

	// Attach/detach the silencer.
	ToggleSilencer();

	// Report next attack time when the viewmodel sequence will be completed.
	m_flNextPrimaryAttack	= gpGlobals->curtime + GetViewModelSequenceDuration();
	m_flNextSecondaryAttack	= gpGlobals->curtime + GetViewModelSequenceDuration();

	// Increase secondary attack call count.
	m_iSecondaryAttacks++;

	// Let the game 'know' the player used secondary attack.
	gamestats->Event_WeaponFired(pPlayer, false, GetClassname());
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int	CWeaponM4A1::GetMinBurst()
{
	return 2;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CWeaponM4A1::GetMaxBurst()
{
	return 5;
}

//-----------------------------------------------------------------------------
const WeaponProficiencyInfo_t *CWeaponM4A1::GetProficiencyValues()
{
	static WeaponProficiencyInfo_t proficiencyTable[] =
	{
		{ 7.0,		0.75 },
		{ 5.00,		0.75 },
		{ 10.0 / 3.0, 0.75 },
		{ 5.0 / 3.0,	0.75 },
		{ 1.00,		1.0 },
	};

	COMPILE_TIME_ASSERT(ARRAYSIZE(proficiencyTable) == WEAPON_PROFICIENCY_PERFECT + 1);

	return proficiencyTable;
}

//-----------------------------------------------------------------------------
// Purpose: Returns true if the silencer is attached.
//-----------------------------------------------------------------------------
const bool& CWeaponM4A1::IsSilencerOn( void ) const
{
	return m_bSilencerOn;
}

//-----------------------------------------------------------------------------
// Purpose: Toggle the silencer.
//-----------------------------------------------------------------------------
void CWeaponM4A1::ToggleSilencer( void )
{
	// If the silencer is attached, call the detach method.
	// If not, call the attach method.
	if (IsSilencerOn())
		DetachSilencer();
	else
		AttachSilencer();
}

//-----------------------------------------------------------------------------
// Purpose: Attach the silencer.
//-----------------------------------------------------------------------------
void CWeaponM4A1::AttachSilencer( void )
{
	// Send the 'attach' weapon activity.
	SendWeaponAnim(ACT_VM_ATTACH_SILENCER);

	// Set silencer inquiry status to true.
	// This way, we will keep track if we need to check
	// if the viewmodel sequence is completed.
	m_bTogglingSilencer = true;
}

//-----------------------------------------------------------------------------
// Purpose: Detach the silencer.
//-----------------------------------------------------------------------------
void CWeaponM4A1::DetachSilencer( void )
{
	// Send the 'detach' weapon activity.
	SendWeaponAnim(ACT_VM_DETACH_SILENCER);

	// Set silencer inquiry status to true.
	// This way, we will keep track if we need to check
	// if the viewmodel sequence is completed.
	m_bTogglingSilencer = true;
}

//-----------------------------------------------------------------------------
// Purpose: Update silencer status.
//-----------------------------------------------------------------------------
void CWeaponM4A1::UpdateSilencer( void )
{
	// Check if we are attaching / detaching the silencer
	// and if the viewmodel sequence is done playing.
	//
	if (m_bTogglingSilencer && IsViewModelSequenceFinished())
	{
		// Toggle silencer attached/detached.
		m_bSilencerOn = !m_bSilencerOn;

		// Let know that we do not need to check anymore if the silencer
		// is being toggled.
		m_bTogglingSilencer = false;
	}
}