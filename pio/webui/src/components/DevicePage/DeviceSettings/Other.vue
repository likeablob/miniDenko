<template>
  <b-field class="level" label="Danger zone" horizontal>
    <b-button
      type="is-danger"
      class="is-fullwidth"
      expanded
      @click="onClickResetLocalMessages"
      >Reset local messages (Show confirmation)</b-button
    >
  </b-field>
</template>

<script>
import { mapState, mapMutations } from 'vuex';

export default {
  data() {
    return {};
  },
  computed: {
    ...mapState(['messages']),
  },
  methods: {
    ...mapMutations(['setMessages']),
    onClickResetLocalMessages() {
      this.$buefy.dialog.confirm({
        title: 'Resetting local messages',
        message:
          'Are you sure you want to <b>reset</b> the saved messages? This action cannot be undone.',
        confirmText: 'Reset',
        type: 'is-danger',
        icon: 'exclamation-triangle',
        hasIcon: true,
        onConfirm: () => {
          this.setMessages(this.messages.filter(v => v.slot !== -1));
          this.$buefy.toast.open('Resetted!');
        },
      });
    },
  },
};
</script>
