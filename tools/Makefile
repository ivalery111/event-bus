USERNAME				= $(shell whoami)
UID						= $(shell id -u)
GID						= $(shell id -g)
IMAGE_NAME              = "event-bus-builder"

docker-build:
	@docker build -t $(IMAGE_NAME) --build-arg UID=$(UID) --build-arg GID=$(GID) --build-arg USERNAME=$(USERNAME) -f Dockerfile . --network host

docker-clean:
	@docker rmi $(IMAGE_NAME)

print-variables:
	@echo "============================================="
	@echo "Variables:"
	@echo "USERNAME - ${USERNAME}"
	@echo "UID      - ${UID}"
	@echo "GID      - ${GID}"
	@echo "============================================="
