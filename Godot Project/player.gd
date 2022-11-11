extends KinematicBody
# How fast the player moves in meters per second.

# The downward acceleration when in the air, in meters per second squared.
export var fall_acceleration = 75

var ball = Sphero.new()

var velocity = Vector3.ZERO
var time = 0
var index = 0;

# Called when the node enters the scene tree for the first time.
func _ready():
	ball.readFiles()
	pass # Replace with function body.

func _physics_process(delta):
	time += delta

	if(time>=ball.getTime(index)):
		velocity.x=(ball.getVX(index))/10
		velocity.z=(ball.getVY(index))/10
		velocity.y -= fall_acceleration * delta
		velocity = move_and_slide(velocity, Vector3.UP)	
		index += 1
	else:
		velocity.x += ball.speedSmootherX(index,(index+1))/10
		velocity.z += ball.speedSmootherY(index,(index+1))/10
		velocity.y -= fall_acceleration * delta

		

