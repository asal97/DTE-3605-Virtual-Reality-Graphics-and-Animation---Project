extends Node
export (PackedScene) var Wall

var time = 0
var index = 0
var ball = Sphero.new()

func _ready():
	ball.readFiles()
	pass # Replace with function body.

func _physics_process(delta):
	time += delta
	if(time>=ball.getTime(index)):
		if(index>=1):
			if(ball.isCollision(index)):
				print(index," ", index+1)
				var orientation = ball.getOR(index)
				print(orientation)
				print("collision coming")
				var wall = Wall.instance()
				var player_position = $player.transform.origin
				var meshs = $player/MeshInstance
				var radius = meshs.mesh.radius * 0.2
				print(radius)
				wall.initialize(player_position,orientation,radius)
				add_child(wall)
		index +=1
# Called when the node enters the scene tree for the first time.

