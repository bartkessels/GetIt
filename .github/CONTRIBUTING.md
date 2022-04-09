To make sure everyone can contribute to GetIt we value the quality and understandability of our code. When you're building
a feature, or patching a bug and you've made a decision. Please document this decision in the [`docs/design.md`](docs/design.md) document.
This will help future contributors understand your rationale. If you've updated some logic in the code, please always update related
test cases or add test cases to test your logic.

## Branching strategy

This project does not use a development branch but uses short lived feature branches which are directly merged into `main`.
We've chosen this strategy 'cause we believe in _release often, release fast_, there's no need for your feature to gather dust in
a stale development branch. However we do have some guidelines:

- If you're contributing a __feature__ use the `feature/<your-feature>` naming convention
- If you're contributing a __bug fix__ use the `bugfix/<bug-name>` naming convention
- If you're contributing to __documentation__ use the `documentation/<type-of-documentation>` naming convention
- If you're contributing a __small fix__, like a version bump to a dependency, use the `hotfix/<hotfix-type>-<name>` naming convention
