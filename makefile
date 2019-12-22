.PHONY: docker_dev docker_tests docker_dev_light docker_tests_light

docker_dev:
	docker-compose build base dev
	docker-compose run --rm dev

docker_tests:
	docker-compose build base tests
	docker-compose run --rm tests

docker_dev_light:
	docker-compose build base_light dev_light
	docker-compose run --rm dev_light

docker_tests_light:
	docker-compose build base_light tests_light
	docker-compose run --rm tests_light
