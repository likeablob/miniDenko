<template>
  <div class="card">
    <header class="card-header">
      <p class="card-header-title level">
        Messages
        <b-field class="level-right">
          <b-button
            @click="onClickAdd()"
            type="is-primary"
            icon-left="plus-square"
            outlined
            icon-pack="fas"
            >Add</b-button
          >
        </b-field>
      </p>
    </header>
    <div class="panel">
      <b-loading
        :is-full-page="false"
        can-cancel
        :active.sync="isLoading"
      ></b-loading>
      <a
        :class="{
          'panel-block': true,
          'is-active': msg.slot !== -1,
        }"
        v-for="(msg, i) in sortedMessages"
        :key="i"
        @click="onClickMsg(msg)"
      >
        <div class="panel-msg">{{ msg.value }}</div>
        <b-button @click.stop="onClickEdit(msg)" icon-pack="fas">Edit</b-button>
      </a>
    </div>
    <b-modal :active.sync="isMessageModalActive" has-modal-card>
      <message-modal :msg="messageModalArg"></message-modal>
    </b-modal>
  </div>
</template>

<script>
import { mapActions, mapState, mapGetters } from 'vuex';
import orderBy from 'lodash/orderBy';

import MessageModal from './MessageModal';

export default {
  name: 'messages',
  components: {
    MessageModal,
  },
  data() {
    return {
      scanResult: [],
      isLoading: false,
      isMessageModalActive: false,
      showmessageionWarn: true,
      messageModalArg: {},
    };
  },
  computed: {
    ...mapState(['messages']),
    ...mapGetters(['savedMessages']),
    sortedMessages() {
      return orderBy(this.messages, v => (v.slot == -1 ? Infinity : v.slot));
    },
  },
  methods: {
    ...mapActions(['postMessage']),
    async onClickMsg(msg) {
      await this.postMessage(msg);
      this.$buefy.toast.open({
        message: 'Updated!',
        type: 'is-success',
      });
    },
    onClickEdit(msg) {
      this.messageModalArg = msg;
      this.isMessageModalActive = true;
    },
    onClickAdd() {
      this.messageModalArg = {};
      this.isMessageModalActive = true;
    },
  },
  async mounted() {},
};
</script>

<style lang="scss" scoped>
.panel-msg {
  width: 100%;
}
</style>
