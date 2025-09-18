# ===[ 기존 변수/타깃은 유지하세요 ]===

# 테스트 설정
TEST_DIR    := tests
TEST_TARGET := exec_smoke

.PHONY: test test-run test-clean test-fclean

# tests/Makefile을 호출해서 빌드
test: minishell
	$(MAKE) -C $(TEST_DIR)

# 빌드 후 바로 실행
test-run: test
	./$(TEST_DIR)/$(TEST_TARGET)

# 테스트 산출물만 정리
test-clean:
	$(MAKE) -C $(TEST_DIR) clean

# 테스트 바이너리까지 완전 정리
test-fclean:
	$(MAKE) -C $(TEST_DIR) fclean

