.PHONY: docker_dev docker_tests

docker_dev:
	docker-compose build base dev
	docker-compose run --rm dev

docker_tests:
	docker-compose build base tests
	docker-compose run --rm tests
