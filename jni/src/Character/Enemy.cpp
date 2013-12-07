#include "Enemy.h"

Enemy::Enemy(Sound* sonido,RosalilaGraphics* painter,Receiver* receiver,std::string name,Player*player, string dificulty)
{
    //Setting up the other variables
    this->name=name;
    this->directory="stages/"+name+"/Enemy/";
    this->sonido=sonido;
    this->painter=painter;
    this->receiver=receiver;
    this->player=player;
    this->active_patterns=new std::list<Pattern*>;
    this->shooting=true;
    this->orientation="idle";
    this->current_type="";
    this->visible=true;

    //Enemy variables
    this->angle=180;
    this->velocity=0;
    this->angle_change=0;


    //Sprites animation
    this->animation_velocity=4;
    this->animation_iteration=0;
    this->current_sprite=0;

    this->iteration=0;

    this->score_upload_message="";
    bool flag_begin_upload=false;

    loadFromXML();

	//Load xml from string

    TiXmlDocument doc_pattern_t;
    doc_pattern_t.Parse("<PatternsFile>	<Type name=\"InitialD\">		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-15\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-5\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"5\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"15\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-15\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-5\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"5\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>		<Pattern				name=\"InitialD\"				velocity=\"20\"				max_velocity=\"10\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"15\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"0\" aim_player=\"yes\" />		</Pattern>	</Type>	<Type name=\"Crazy eyes\">		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"20\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"40\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"60\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"80\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"100\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"120\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"140\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"160\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"200\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"220\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"240\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"260\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\">		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"280\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"300\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"320\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Crazy eyes\"				velocity=\"14\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"340\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-45\"				offset_y=\"145\"				startup=\"0\"				cooldown=\"80\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern> </Type>	<Type name=\"Happy meal\">		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"10\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"12\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"15\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"17\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"10\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"12\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"15\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"17\" angle=\"180\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"0\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"2\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"5\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"7\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"10\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"12\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"15\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"17\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"2\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"5\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"7\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"10\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"12\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"15\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"20\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"-90\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"20\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"17\" angle=\"0\"/>		</Pattern>		<Pattern				name=\"Happy meal\"				velocity=\"0\"				max_velocity=\"16\"				acceleration=\"1\"				a_frequency=\"1\"				angle=\"0\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"25\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>	</Type>	<Type name=\"Rockets\">		<Pattern				name=\"Rockets\"				velocity=\"3\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"0\"				offset_y=\"0\"				startup=\"0\"				cooldown=\"10\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Rockets\"				velocity=\"-1\"				max_velocity=\"30\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"120\"				ac_frequency=\"60\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-70\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"50\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Rockets\"				velocity=\"-1\"				max_velocity=\"30\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"120\"				ac_frequency=\"60\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"70\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"50\"				duration=\"600\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern> 	</Type>	<Type name=\"Feminist Laser\">		<Pattern				name=\"Feminist Laser\"				velocity=\"0\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Feminist Laser startup\"				offset_x=\"-945\"				offset_y=\"150\"				startup=\"0\"				cooldown=\"100\"				duration=\"11\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Feminist Laser\"				velocity=\"0\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Feminist Laser active\"				offset_x=\"-945\"				offset_y=\"150\"				startup=\"11\"				cooldown=\"100\"				duration=\"75\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"Feminist Laser\"				velocity=\"0\"				max_velocity=\"30\"				acceleration=\"0\"				a_frequency=\"10\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Feminist Laser cooldown\"				offset_x=\"-945\"				offset_y=\"150\"				startup=\"86\"				cooldown=\"100\"				duration=\"11\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>	</Type>	<Type name=\"KowaiiDesu\">		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"-30\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"30\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"-70\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"70\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"-110\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"110\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"-150\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"0\"				max_velocity=\"20\"				acceleration=\"1\"				a_frequency=\"0\"				angle=\"180\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Eye Lazor\"				offset_x=\"-80\"				offset_y=\"220\"				startup=\"0\"				cooldown=\"5\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >					<Modifier at=\"20\" angle=\"150\"/>		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"2\"				max_velocity=\"10\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"-4\"				stop_ac_at=\"-1\"				ac_frequency=\"3\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"-1\"				random_angle=\"360\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"2\"				max_velocity=\"10\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"-4\"				stop_ac_at=\"-1\"				ac_frequency=\"3\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"-75\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"-1\"				random_angle=\"360\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"2\"				max_velocity=\"10\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"-4\"				stop_ac_at=\"-1\"				ac_frequency=\"3\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"-1\"				random_angle=\"360\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"2\"				max_velocity=\"10\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"-4\"				stop_ac_at=\"-1\"				ac_frequency=\"3\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"0\"				cooldown=\"80\"				duration=\"-1\"				random_angle=\"360\"				aim_player=\"no\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>		<Pattern				name=\"KowaiiDesu\"				velocity=\"2\"				max_velocity=\"5\"				acceleration=\"1\"				a_frequency=\"10\"				angle=\"0\"				angle_change=\"0\"				stop_ac_at=\"-1\"				ac_frequency=\"0\"				animation_velocity=\"2\"				bullet=\"Rocket\"				offset_x=\"50\"				offset_y=\"240\"				startup=\"10\"				cooldown=\"80\"				duration=\"-1\"				random_angle=\"0\"				aim_player=\"yes\"				bullet_rotation=\"0\"				br_change=\"0\"				independent_br=\"no\" >		</Pattern>	</Type></PatternsFile>"
        , 0, TIXML_ENCODING_UTF8);
    TiXmlDocument *doc_pattern;
    doc_pattern=&doc_pattern_t;
    TiXmlNode *patterns_file=doc_pattern->FirstChild("PatternsFile");

    //Loading patterns
    for(TiXmlNode* pattern_type=patterns_file->FirstChild("Type");
            pattern_type!=NULL;
            pattern_type=pattern_type->NextSibling("Type"))
    {
        std::string type_name=pattern_type->ToElement()->Attribute("name");
        std::vector<Pattern*> patterns;
        int pattern_number=0;
        for(TiXmlNode* pattern_node=pattern_type->FirstChild("Pattern");
                pattern_node!=NULL;
                pattern_node=pattern_node->NextSibling("Pattern"))
        {

            std::string bullet_name=pattern_node->ToElement()->Attribute("bullet");
            Bullet*bullet=bullets[bullet_name];

            int velocity=0;
            if(pattern_node->ToElement()->Attribute("velocity")!=NULL)
                velocity=atoi(pattern_node->ToElement()->Attribute("velocity"));

            int max_velocity=9999999;
            if(pattern_node->ToElement()->Attribute("max_velocity")!=NULL)
                max_velocity=atoi(pattern_node->ToElement()->Attribute("max_velocity"));

            int acceleration=0;
            if(pattern_node->ToElement()->Attribute("acceleration")!=NULL)
                acceleration=atoi(pattern_node->ToElement()->Attribute("acceleration"));

            int a_frequency=0;
            if(pattern_node->ToElement()->Attribute("a_frequency")!=NULL)
                a_frequency=atoi(pattern_node->ToElement()->Attribute("a_frequency"));

            int angle=0;
            if(pattern_node->ToElement()->Attribute("angle")!=NULL)
                angle=atoi(pattern_node->ToElement()->Attribute("angle"));

            int angle_change=0;
            if(pattern_node->ToElement()->Attribute("angle_change")!=NULL)
                angle_change=atoi(pattern_node->ToElement()->Attribute("angle_change"));

            int stop_ac_at=-1;
            if(pattern_node->ToElement()->Attribute("stop_ac_at")!=NULL)
                stop_ac_at=atoi(pattern_node->ToElement()->Attribute("stop_ac_at"));

            int ac_frequency=0;
            if(pattern_node->ToElement()->Attribute("ac_frequency")!=NULL)
                ac_frequency=atoi(pattern_node->ToElement()->Attribute("ac_frequency"));

            int offset_x=0;
            if(pattern_node->ToElement()->Attribute("offset_x")!=NULL)
                offset_x=atoi(pattern_node->ToElement()->Attribute("offset_x"));

            int offset_y=0;
            if(pattern_node->ToElement()->Attribute("offset_y")!=NULL)
                offset_y=atoi(pattern_node->ToElement()->Attribute("offset_y"));

            int startup=0;
            if(pattern_node->ToElement()->Attribute("startup")!=NULL)
                startup=atoi(pattern_node->ToElement()->Attribute("startup"));

            int cooldown=0;
            if(pattern_node->ToElement()->Attribute("cooldown")!=NULL)
                cooldown=atoi(pattern_node->ToElement()->Attribute("cooldown"));

            int animation_velocity=0;
            if(pattern_node->ToElement()->Attribute("animation_velocity")!=NULL)
                animation_velocity=atoi(pattern_node->ToElement()->Attribute("animation_velocity"));

            int duration=-1;
            if(pattern_node->ToElement()->Attribute("duration"))
                duration=atoi(pattern_node->ToElement()->Attribute("duration"));

            int random_angle=0;
            if(pattern_node->ToElement()->Attribute("random_angle"))
                random_angle=atoi(pattern_node->ToElement()->Attribute("random_angle"));

            bool aim_player=false;
            if(pattern_node->ToElement()->Attribute("aim_player"))
                aim_player=strcmp(pattern_node->ToElement()->Attribute("aim_player"),"yes")==0;

            int bullet_rotation=0;
            if(pattern_node->ToElement()->Attribute("bullet_rotation"))
                bullet_rotation=atoi(pattern_node->ToElement()->Attribute("bullet_rotation"));

            int br_change=0;
            if(pattern_node->ToElement()->Attribute("br_change"))
                br_change=atoi(pattern_node->ToElement()->Attribute("br_change"));

            bool independent_br=false;
            if(pattern_node->ToElement()->Attribute("independent_br"))
                independent_br=strcmp(pattern_node->ToElement()->Attribute("independent_br"),"yes")==0;

            addPattern(sonido,painter,receiver,
                                    type_name,
                                    velocity,
                                    max_velocity,
                                    acceleration,
                                    a_frequency,
                                    angle,
                                    angle_change,
                                    stop_ac_at,
                                    ac_frequency,
                                    animation_velocity,
                                    bullet_name,
                                    offset_x,
                                    offset_y,
                                    startup,
                                    cooldown,
                                    duration,
                                    random_angle,
                                    aim_player,
                                    bullet_rotation,
                                    br_change,
                                    independent_br);

            if(pattern_node->FirstChild("Modifier")!=NULL)
            for(TiXmlNode* pattern_modifier_node=pattern_node->FirstChild("Modifier");
                    pattern_modifier_node!=NULL;
                    pattern_modifier_node=pattern_modifier_node->NextSibling("Modifier"))
            {
                int at=atoi(pattern_modifier_node->ToElement()->Attribute("at"));

                if(pattern_modifier_node->ToElement()->Attribute("bullet")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("bullet");
                    addModifier(type_name,pattern_number,at, "bullet", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("velocity")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("velocity");
                    addModifier(type_name,pattern_number,at, "velocity", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("max_velocity")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("max_velocity");
                    addModifier(type_name,pattern_number,at, "max_velocity", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("acceleration")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("acceleration");
                    addModifier(type_name,pattern_number,at, "acceleration", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("a_frequency")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("a_frequency");
                    addModifier(type_name,pattern_number,at, "a_frequency", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("angle")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("angle");
                    addModifier(type_name,pattern_number,at, "angle", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("angle_change")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("angle_change");
                    addModifier(type_name,pattern_number,at, "angle_change", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("stop_ac_at")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("stop_ac_at");
                    addModifier(type_name,pattern_number,at, "stop_ac_at", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("ac_frequency")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("ac_frequency");
                    addModifier(type_name,pattern_number,at, "ac_frequency", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("animation_velocity")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("animation_velocity");
                    addModifier(type_name,pattern_number,at, "animation_velocity", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("offset_x")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("offset_x");
                    addModifier(type_name,pattern_number,at, "offset_x", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("offset_y")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("offset_y");
                    addModifier(type_name,pattern_number,at, "offset_y", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("startup")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("startup");
                    addModifier(type_name,pattern_number,at, "startup", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("cooldown")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("cooldown");
                    addModifier(type_name,pattern_number,at, "cooldown", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("duration")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("duration");
                    addModifier(type_name,pattern_number,at, "duration", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("random_angle")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("random_angle");
                    addModifier(type_name,pattern_number,at, "random_angle", value);
                }

                if(pattern_modifier_node->ToElement()->Attribute("aim_player")!=NULL)
                {
                    std::string value=pattern_modifier_node->ToElement()->Attribute("aim_player");
                    addModifier(type_name,pattern_number,at, "aim_player", value);
                }
            }
            pattern_number++;
        }
    }

    loadModifiersFromXML();
    life_bar=painter->getTexture(directory+"life_bar.png");
}

void Enemy::modifiersControl()
{
    bool flag_iterator_change=false;

    vector<Modifier*>* current_modifiers = this->modifiers[iteration];
    if(current_modifiers!=NULL)
    {
        for(int i=0;i<(int)current_modifiers->size();i++)
        {
            Modifier* modifier=(*current_modifiers)[i];
            if(modifier->variable=="velocity")
            {
                this->velocity=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="angle")
            {
                this->angle=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="angle_change")
            {
                this->angle_change=atoi(modifier->value.c_str());
            }
            if(modifier->variable=="iterator")
            {
                this->iteration=atoi(modifier->value.c_str());
                flag_iterator_change=true;
            }
            if(modifier->variable=="pattern_type")
            {
                this->current_type=modifier->value;
            }
        }
    }

    if(!flag_iterator_change && getIterateSlowdownFlag())
        iteration++;
}

void Enemy::logic(int stage_velocity, string stage_name, int global_iteration, string username)
{
    animationControl();
    spellControl(stage_velocity);

    for (std::list<Pattern*>::iterator pattern = active_patterns->begin(); pattern != active_patterns->end(); pattern++)
        if(((Pattern*)*pattern)->getAimPlayer())
        {
            double distance_x=player->x-((Pattern*)*pattern)->getX();
            double distance_y=player->y-((Pattern*)*pattern)->getY();
            ((Pattern*)*pattern)->setAngle(((Pattern*)*pattern)->getAngle()-atan2(distance_y,distance_x)*180/PI);
        }

    if(this->hp>0)
	{
        modifiersControl();
	}
    else
    {
        if(orientation!="destroyed" && flag_begin_upload)
        {
            orientation="destroyed";
            if(this->sonido->soundExists(name+".destroyed"))
                this->sonido->playSound(name+".destroyed");

            this->hitbox.setValues(0,0,0,0,0);

            //Delete bullets
            std::list<Pattern*>* active_patterns=getActivePatterns();
            std::list<Pattern*>::iterator i = active_patterns->begin();
            while (i != active_patterns->end())
            {
                Pattern*p=(Pattern*)*i;
                active_patterns->erase(i++);
                delete p;
            }

            RosalilaNetwork network(painter);
            //score_upload_message = network.runTcpClientSendScore(31716, "108.59.1.187",stage_name, username, global_iteration);
            score_upload_message = network.runTcpClientSendScore(31716, "localhost",stage_name, username, global_iteration);
        }
    }

    this->angle+=this->angle_change / getSlowdown();

    this->x += cos (angle*PI/180) * velocity / getSlowdown() + stage_velocity;
    this->y -= sin (angle*PI/180) * velocity / getSlowdown();

    getIterateSlowdownFlag();
}

void Enemy::render()
{
    parrentRender();
}

void Enemy::renderHUD()
{
    painter->drawRectangle(life_bar_x+life_bar_rect_offset_x,life_bar_y+life_bar_rect_offset_y,(life_bar_rect_width*hp)/max_hp,life_bar_rect_height,0,this->color.getRed(),this->color.getGreen(),this->color.getBlue(),this->color.getAlpha(),false);

    painter->draw2DImage
    (   life_bar,
        life_bar->getWidth(),life_bar->getHeight(),
        painter->camera_x+life_bar_x,life_bar_y,
        1.0,
        0.0,
        false,
        0,0,
        Color(255,255,255,255),
        true);
    if(this->hp<=0)
    {
        painter->drawText("Uploading score.",0,80);
        painter->drawText(score_upload_message,0,95);
        flag_begin_upload = true;
    }
}

void Enemy::addEnemyModifier(int at,std::string variable,std::string value)
{
	//Create new if not exists
	std::map<int, vector<Modifier*>* >::const_iterator it = modifiers.find(at);
	if(it==modifiers.end())
	{
		vector<Modifier*>* temp_modifiers=new vector<Modifier*>();
		modifiers[at]=temp_modifiers;
	}

	this->modifiers[at]->push_back(new Modifier(variable,value));
}

void Enemy::loadModifiersFromXML()
{
	addEnemyModifier(0,"velocity","2");
	addEnemyModifier(0,"angle_change","5");

	addEnemyModifier(100,"pattern_type","InitialD");

	addEnemyModifier(500,"pattern_type","");

	addEnemyModifier(550,"pattern_type","Crazy eyes");

	addEnemyModifier(1050,"pattern_type","");
	addEnemyModifier(1050,"velocity","0");
	addEnemyModifier(1050,"angle_change","0");

	addEnemyModifier(1140,"velocity","4");
	addEnemyModifier(1140,"angle","-90");

	addEnemyModifier(1200,"pattern_type","Happy meal");
	addEnemyModifier(1200,"velocity","0");

	for(int i=0;i<4;i++)
	{
		addEnemyModifier(1400+i*50,"velocity","4");
		addEnemyModifier(1400+i*50,"angle","180");
	}

	for(int i=0;i<4;i++)
	{
		addEnemyModifier(1425+i*50,"angle","0");
	}

	for(int i=0;i<5;i++)
	{
		addEnemyModifier(1650+i*75,"angle","180");
	}

	for(int i=0;i<4;i++)
	{
		addEnemyModifier(1675+i*75,"angle","-60");
	}

	for(int i=0;i<4;i++)
	{
		addEnemyModifier(1700+i*75,"angle","60");
	}

	addEnemyModifier(1975,"velocity","0");
	addEnemyModifier(1975,"angle","180");

	addEnemyModifier(2030,"pattern_type","");
	addEnemyModifier(2030,"velocity","5");
	addEnemyModifier(2030,"angle","-90");

	addEnemyModifier(2075,"pattern_type","Rockets");
	addEnemyModifier(2075,"velocity","5");

	addEnemyModifier(2075,"angle","90");
	addEnemyModifier(2175,"angle","-90");
	addEnemyModifier(2275,"angle","90");

	addEnemyModifier(2375,"pattern_type","Feminist Laser");
	addEnemyModifier(2375,"velocity","0");
	addEnemyModifier(2575,"pattern_type","");

	addEnemyModifier(2675,"pattern_type","Rockets");
	addEnemyModifier(2675,"velocity","5");
	addEnemyModifier(2675,"angle","-90");
	addEnemyModifier(2775,"angle","90");
	addEnemyModifier(2875,"angle","-90");
	addEnemyModifier(2975,"angle","90");
	addEnemyModifier(3075,"angle","-90");
	addEnemyModifier(3175,"angle","90");

	addEnemyModifier(3275,"pattern_type","Feminist Laser");
	addEnemyModifier(3275,"velocity","0");
	addEnemyModifier(3475,"pattern_type","");

	addEnemyModifier(3575,"pattern_type","Rockets");
	addEnemyModifier(3575,"velocity","5");
	addEnemyModifier(3575,"angle","-90");

	addEnemyModifier(3675,"angle","90");
	addEnemyModifier(3775,"angle","-90");
	addEnemyModifier(3875,"angle","90");
	addEnemyModifier(3975,"angle","-90");

	addEnemyModifier(4075,"pattern_type","");
	addEnemyModifier(4075,"angle","90");

	addEnemyModifier(4175,"velocity","0");
	addEnemyModifier(4275,"pattern_type","KowaiiDesu");
/**/
}

void Enemy::addActivePattern(Pattern* pattern)
{
    Pattern* pattern_temp=new Pattern(pattern,this->x,this->y);
    float angle=pattern_temp->getAngle();
    angle+=pattern_temp->getRandomAngle();

    pattern_temp->setAngle(angle);

    if(pattern_temp->getAimPlayer())
    {
        double distance_x=player->x-pattern_temp->getX();
        double distance_y=player->y-pattern_temp->getY();
        pattern_temp->setAngle(pattern_temp->getAngle()-atan2(distance_y,distance_x)*180/PI);
    }

    active_patterns->push_back(pattern_temp);
}
